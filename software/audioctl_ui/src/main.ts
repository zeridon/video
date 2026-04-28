import favicon_dataurl from "../assets/favicon.png?url&inline"
import { MixerUI } from "./mixer_ui.tsx"
import { WSClient } from "misirka"

function setup_favicon() {
  const link = document.querySelector<HTMLLinkElement>("#favicon")!
  link.rel = "icon"
  link.type = "image/png"
  link.href = favicon_dataurl
}

function main() {
  setup_favicon()
  const mclient = new WSClient(ws_url())
  const ui = new MixerUI(mclient, document.querySelector<HTMLDivElement>('#mixer')!)

  document.querySelector<HTMLButtonElement>('#setup-mode')!.onclick = () => ui.toggleSetupMode()
}

function ws_url() {
  const protocol = location.protocol === "https:" ? "wss" : "ws"
  return `${protocol}://${location.host}/ws`
}

main()
