import type {MisirkaClient} from "misirka"
import {MixerClient} from "./mixerclient.ts"
import type {Levels, MixerState} from "./api_data.ts"

import {element, fragment} from "tsx-vanilla"
import {Input, Output} from "./components.tsx"
import {formatDb, logLinear} from "./helpers.ts"


export class MixerUI {
  constructor(mclient: MisirkaClient, private container: HTMLElement) {
    this.client = new MixerClient(mclient)
    mclient.on_alive(() => this.on_alive())
    mclient.on_dead(() => this.on_dead())

    this.container.textContent = 'connecting'
  }

  private client: MixerClient


  private async on_alive() {
    const initialState = await this.client.get_state()

    const inputsContainer = <div className='inputs channellist'/>
    const outputsContainer = <div className='outputs channellist'/>

    const container = <>
      <div className='mixer'>
        <h2>Inputs</h2>
        {inputsContainer}
      </div>
      <div className='mixer'>
        <h2>Outputs</h2>
        {outputsContainer}
      </div>
    </>


    this.container.replaceChildren(container)

    this.setupInputs(inputsContainer as HTMLDivElement, initialState)
    this.setupOutputs(outputsContainer as HTMLDivElement, initialState)
    await this.client.subscribe_state((state) => this.updateState(state))
    await this.client.subscribe_levels((levels) => this.updateVu(initialState, levels))
  }

  private async on_dead() {
    this.destroy_ui()
  }


  private destroy_ui() {
    this.container.textContent = 'reconnecting'
  }

  private async updateVu(state: MixerState, levels: Levels) {
    for (const [i, db] of levels.smooth.inputs.entries()) {
      const input = state.channels[i].name

      const meter = document.querySelector<HTMLMeterElement>(`.channel[data-name=${input}] meter`)
      if(meter) meter.value = logLinear(db)
      const text = document.querySelector<HTMLDivElement>(`.channel[data-name=${input}] .meterdb`)
      if(text) text.innerText = formatDb(db)

    }
    for (const [i, db] of levels.smooth.buses.entries()) {
      const output = state.buses[i]
      const meter = document.querySelector<HTMLMeterElement>(`.channel[data-name=${output.name}] meter`)
      if(meter) meter.value = logLinear(db)
      const text = document.querySelector<HTMLDivElement>(`.channel[data-name=${output.name}] .meterdb`)
      if(text) text.innerText = formatDb(db)
    }
  }

  private async updateState(state: MixerState) {
    for (const channel of state.channels) {
      for (const [i, props] of channel.sends.entries()) {
        const output = state.buses[i]
        const checkbox = document.getElementById(`mute-${channel.name}-${output.name}`) as HTMLInputElement
        if (checkbox) checkbox.checked = !props.unmuted
      }
    }
    for (const channel of state.channels) {
      const slider = document.querySelector<HTMLInputElement>(`.inputs [data-name=${channel.name}] input[type=range]`)
      if(slider) slider.value = channel.gain.toString()

      const text = document.querySelector<HTMLDivElement>(`.inputs [data-name=${channel.name}] .gaindb`)
      if(text) text.innerText = formatDb(channel.gain)
    }
    for (const bus of state.buses) {
      const slider = document.querySelector<HTMLInputElement>(`.outputs [data-name=${bus.name}] input[type=range]`)
      if(slider) slider.value = bus.volume.toString()

      const text = document.querySelector<HTMLDivElement>(`.outputs [data-name=${bus.name}] .gaindb`)
      if(text) text.innerText = formatDb(bus.volume)
    }
  }

  private setupOutputs(container: HTMLDivElement, state: MixerState) {
    container.replaceChildren(
      ...state.buses.entries().map(([i, out]) =>
        <Output output={out}
          onVolume={volume => this.client.set_bus_volume(i, volume)}
        />),
    )
  }

  private setupInputs(container: HTMLDivElement, state: MixerState) {
    container.replaceChildren(
      ...state.channels.entries().map(([i, inp]) =>
        <Input input={inp} state={state}
          onGain={gain => this.client.set_in_gain(i, gain)} 
          onSendMute={bus => muted => this.client.set_matrix_send(i, bus, muted)}
          onSendVolume={bus => volume => this.client.set_matrix_volume(i, bus, volume)}
        />),
    )
  }
}
