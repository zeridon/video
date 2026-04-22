import { MixerClient } from "./mixerclient.ts"
import type { MisirkaClient } from "misirka"
import type { MixerState, Levels } from "./api_data.ts"

export class MixerUI {
  constructor(mclient: MisirkaClient, private container: HTMLElement) {
    this.client = new MixerClient(mclient)
    mclient.on_alive(() => { this.on_alive() })
    mclient.on_dead(() => { this.on_dead() })

    this.container.textContent = 'connecting'
  }

  private async on_alive() {
    const initial_state = await this.client.get_state()
    this.build_ui(initial_state)
    await this.client.subscribe_state(
      (state: MixerState) => { this.handle_state(state) },
    )
    await this.client.subscribe_levels(
      (levels: Levels) => { this.handle_levels(levels) },
    )
  }

  private async on_dead() {
    this.destroy_ui()
  }
  private build_ui(state: MixerState) {
    this.container.innerHTML = ''

    this.phantomChecks = []
    this.inputGainSliders = []
    this.sendUnmuteChecks = []
    this.sendVolumeSliders = []
    this.busVolumeSliders = []
    this.levelIndicators = []
    this.levelValues = []

    const mixer = document.createElement('div')
    mixer.className = 'mixer-container'

    const chSection = document.createElement('div')
    chSection.className = 'channels section'

    const chSectionNameEl = document.createElement('div')
    chSectionNameEl.className = 'section-header'
    chSectionNameEl.textContent = 'input channels'

    chSection.append(chSectionNameEl)

    for (const [ci, ch] of state.channels.entries()) {
      const strip = document.createElement('div')
      strip.className = 'channel-box section'

      const nameEl = document.createElement('div')
      nameEl.className = 'section-header'
      nameEl.textContent = `${ch.label}: ${ch.name}`
      nameEl.title = ch.name

      const inputBox = document.createElement('div')
      inputBox.className = 'input-box slot'

      const gainLabel = document.createElement('div')
      gainLabel.className = 'strip-label'
      gainLabel.textContent = 'gain: '

      const gainSlider = document.createElement('input')
      gainSlider.type = 'range'
      gainSlider.className = 'gain-slider'
      gainSlider.min = String(-80)
      gainSlider.max = String(60)
      gainSlider.step = '0.6'
      gainSlider.value = String(ch.gain)

      const gainVal = document.createElement('div')
      gainVal.className = 'db-value'
      gainVal.textContent = formatDb(ch.gain)
      gainSlider.oninput = async () => {
        await this.client.set_in_gain(ci, parseFloat(gainSlider.value))
        gainVal.textContent = formatDb(parseFloat(gainSlider.value))
      }
      this.inputGainSliders.push([gainSlider, gainVal])

      const phantomBox = document.createElement('span')
      phantomBox.className = 'enable-box'

      const phantomCheck = document.createElement('input')
      phantomCheck.type = 'checkbox'
      phantomCheck.id = `phantom-${ci}`
      phantomCheck.checked = ch.phantom
      phantomCheck.oninput = async () => {
        await this.client.set_phantom(ci, phantomCheck.checked)
      }
      this.phantomChecks.push(phantomCheck)

      const phantomLabel = document.createElement('label')
      phantomLabel.htmlFor = phantomCheck.id
      phantomLabel.className = 'phantom-label'
      phantomLabel.textContent = '👻'

      phantomBox.append(phantomLabel, phantomCheck)

      inputBox.append(gainLabel, gainSlider, gainVal, phantomBox)

      const sendsSection = document.createElement('div')
      sendsSection.className = 'sends-section'

      const chanSendUnmuteChecks: Array<HTMLInputElement> = []
      const chanSendVolumeSliders: Array<[HTMLInputElement, HTMLElement]> = []
      for (const [bi, send] of ch.sends.entries()) {
        const bus = state.buses[bi]
        const slot = document.createElement('div')
        slot.className = 'send-box slot'

        const busTag = document.createElement('div')
        busTag.className = 'send-bus-tag'
        busTag.textContent = `${ch.label} → ${bus.label}: `

        // mute toggle
        const unmuteBox = document.createElement('span')
        unmuteBox.className = 'enable-box'

        const sendCheck = document.createElement('input')
        sendCheck.type = 'checkbox'
        sendCheck.id = `unmute-${ci}-${bi}`
        sendCheck.checked = send.unmuted
        sendCheck.oninput = async () => {
          await this.client.set_matrix_send(ci, bi, sendCheck.checked)
        }
        chanSendUnmuteChecks.push(sendCheck)

        const sendCheckLabel = document.createElement('label')
        sendCheckLabel.htmlFor = sendCheck.id
        sendCheckLabel.textContent = '🔈️'

        unmuteBox.append(sendCheckLabel, sendCheck)

        // send level
        const sendSlider = document.createElement('input')
        sendSlider.type = 'range'
        sendSlider.min = '-80'
        sendSlider.max = '20'
        sendSlider.step = '0.5'
        sendSlider.value = String(send.volume)
        sendSlider.oninput = async () => {
          await this.client.set_matrix_volume(ci, bi, parseFloat(sendSlider.value))
          sendVal.textContent = formatDb(parseFloat(sendSlider.value))
        }

        const sendVal = document.createElement('div')
        sendVal.className = 'db-value'
        sendVal.textContent = formatDb(send.volume)
        chanSendVolumeSliders.push([sendSlider, sendVal])

        slot.append(busTag, unmuteBox, sendSlider, sendVal)
        sendsSection.append(slot)
      }
      this.sendUnmuteChecks.push(chanSendUnmuteChecks)
      this.sendVolumeSliders.push(chanSendVolumeSliders)

      const levelIndicator = this.makeLevelIndicator()
      strip.append(nameEl, inputBox, levelIndicator, sendsSection)
      chSection.append(strip)
    }

    const busesSection = document.createElement('div')
    busesSection.className = 'buses section'

    const busesSectionNameEl = document.createElement('div')
    busesSectionNameEl.className = 'section-header'
    busesSectionNameEl.textContent = 'output buses'

    busesSection.append(busesSectionNameEl)

    for (const [bi, bus] of state.buses.entries()) {
      const busSection = document.createElement('div')
      busSection.className = 'bus section'

      const nameEl = document.createElement('div')
      nameEl.className = 'bus-name section-header'
      nameEl.textContent = `${bus.label}: ${bus.name}`
      nameEl.title = bus.name

      busSection.append(nameEl)

      const strip = document.createElement('div')
      strip.className = 'bus-strip slot'

      const volSlider = document.createElement('input')
      volSlider.type = 'range'
      volSlider.className = 'fader vertical'
      volSlider.min = '-80'
      volSlider.max = '20'
      volSlider.step = '0.5'
      volSlider.value = String(bus.volume)

      const volVal = document.createElement('div')
      volVal.className = 'db-value'
      volVal.textContent = formatDb(bus.volume)
      volSlider.oninput = async () => {
        await this.client.set_bus_volume(bi, parseFloat(volSlider.value))
        volVal.textContent = formatDb(parseFloat(volSlider.value))
      }
      this.busVolumeSliders.push([volSlider, volVal])

      strip.append(volSlider, volVal)
      const levelIndicator = this.makeLevelIndicator()
      busSection.append(strip, levelIndicator)
      busesSection.append(busSection)
    }

    mixer.append(chSection, busesSection)
    this.container.append(mixer)
  }

  private makeLevelIndicator(): HTMLElement {
    const slot = document.createElement('div')
    slot.className = 'level-indicator slot'

    const label = document.createElement('div')
    label.textContent = 'level: '

    const container = document.createElement('div')
    container.className = 'container'

    const inner = document.createElement('div')
    inner.className = 'inner'
    inner.setAttribute('style', 'width: 0%')
    container.append(inner)
    this.levelIndicators.push(inner)

    const val = document.createElement('div')
    val.className = 'db-value'
    this.levelValues.push(val)

    slot.append(label, container, val)

    return slot
  }

  private destroy_ui() {
    this.container.textContent = 'reconnecting'
  }

  private handle_state(state: MixerState) {
    // TODO: if the shape of the arrays or names, etc, is different from
    // the current ones, rebuild UI
    for (const [i, ch] of state.channels.entries()) {
      this.inputGainSliders[i][0].value = String(ch.gain)
      this.inputGainSliders[i][1].textContent = formatDb(ch.gain)
      this.phantomChecks[i].checked = ch.phantom
      for (const [j, _] of state.buses.entries()) {
        this.sendUnmuteChecks[i][j].checked = ch.sends[j].unmuted
        this.sendVolumeSliders[i][j][0].value = String(ch.sends[j].volume)
        this.sendVolumeSliders[i][j][1].textContent = formatDb(ch.sends[j].volume)
      }
    }
    for (const [j, bus] of state.buses.entries()) {
      this.busVolumeSliders[j][0].value = String(bus.volume)
      this.busVolumeSliders[j][1].textContent = formatDb(bus.volume)
    }
  }

  private handle_levels(levels: Levels) {
    for (const [i, db] of [...levels.smooth.inputs, ...levels.smooth.buses].entries()) {
      const pct = 100 * 0.79306 * Math.exp(db * 0.0527087)
      this.levelIndicators[i].style = `width: ${pct}%`
      this.levelValues[i].textContent = formatDb(db)
    }
  }

  private phantomChecks: Array<HTMLInputElement> = []
  private inputGainSliders: Array<[HTMLInputElement, HTMLElement]> = []
  private sendUnmuteChecks: Array<Array<HTMLInputElement>> = []
  private sendVolumeSliders: Array<Array<[HTMLInputElement, HTMLElement]>> = []
  private busVolumeSliders: Array<[HTMLInputElement, HTMLElement]> = []
  private levelIndicators: Array<HTMLElement> = []
  private levelValues: Array<HTMLElement> = []
  private client: MixerClient
}

function formatDb(n: number): string {
  const sign = n < 0 ? '-' : '\u00A0'
  const abs = Math.abs(n)
  const intPart = String(Math.floor(abs)).padStart(3, '0')
  const decPart = Math.floor((abs % 1) * 10)
  return `${sign}${intPart}.${decPart} dB`
}
