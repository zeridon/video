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

  private build_ui(_state: MixerState) {
    this.container.textContent = 'connected'
  }

  private destroy_ui() {
    this.container.textContent = 'reconnecting'
  }

  private handle_state(state: MixerState) {
    console.log('got state: ', state)
  }

  private handle_levels(levels: Levels) {
    this.container.textContent = `levels: ${JSON.stringify(levels, null, 2)}`
  }

  private client: MixerClient
}
