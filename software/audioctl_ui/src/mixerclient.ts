import type { MisirkaClient } from "misirka"
import { MixerStateSchema, LevelsSchema } from "./api_data.ts"
import type { MixerState, Levels } from "./api_data.ts"

export class MixerClient {
  constructor(private client: MisirkaClient) {
  }

  async get_state(): Promise<MixerState> {
    return await this.client.get('state', MixerStateSchema)
  }

  async subscribe_state(handler: (state: MixerState) => void) {
    await this.client.subscribe(
      ['state'], MixerStateSchema, handler,
    )
  }

  async subscribe_levels(handler: (levels: Levels) => void) {
    await this.client.subscribe(
      ['levels'], LevelsSchema, handler,
    )
  }
}
