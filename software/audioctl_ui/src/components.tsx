import type {BusState, ChannelState, MixerState} from "./api_data"
import {element} from "tsx-vanilla"

export const VolumeSlider = (props: {onVolume: (volume: number) => void})=>
  <div>
    <input type='range' min='-80' max='60' step='0.6'
      oninput={(e) => props.onVolume(+e.target.value)}/>
    <div className='db gaindb'/>
  </div> as HTMLDivElement

export const Output = (props: {output: BusState, onVolume: (volume: number) => void}) =>
    <div className='channel' dataset={{name: props.output.name}}>
      <h3>{props.output.label}</h3>
      <div className='sliders'>
        <VolumeSlider onVolume={(volume) => props.onVolume(volume)}/>
        <Meter/>
      </div>
    </div> as HTMLDivElement

export const Meter = () =>
    <div><meter min={0} max={1} low={0.5} optimum={0.2} high={0.8}/>
      <div className='db meterdb'/>
    </div> as HTMLDivElement

export const Send = (props: {input: ChannelState, output: BusState, onMute: (muted: boolean) => void, onVolume: (volume: number) => void}) =>
    <div>
      <label htmlFor={`mute-${props.input.name}-${props.output.name}`}>{props.output.name}</label>
      <input type='checkbox'
        id={`mute-${props.input.name}-${props.output.name}`}
        oninput={(e) => props.onMute(!e.target.checked)}/>
    </div> as HTMLDivElement

export const Input = (props: {input: ChannelState, state: MixerState, onGain: (gain: number) => void, onSendVolume: (id: number) => (volume: number) => void, onSendMute: (id: number) => (muted: boolean) => void}) => {
  const mutes = props.input.sends.entries().map(([i, _]) =>
    <Send input={props.input} output={props.state.buses[i]} 
      onMute={props.onSendMute(i)} onVolume={props.onSendVolume(i)}
    />)

  return <div className='channel' dataset={{name: props.input.name}}>
    <h3>{props.input.label}</h3>
    <div className='sliders'>
      <VolumeSlider onVolume={(volume) => props.onGain(volume)}/>
      <Meter/>
    </div>
    <div className='mutes'>
            {...mutes.toArray()}
    </div>
  </div> as HTMLDivElement
}
