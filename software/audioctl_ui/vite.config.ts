import { defineConfig } from "vite"
import { viteSingleFile } from "vite-plugin-singlefile"
import viteCompression from "vite-plugin-compression"
import checker from 'vite-plugin-checker'

export default defineConfig(({ mode }) => {
  let server_cfg = {}
  let optimize_deps = {}

  if (mode === "development") {
    const api_url = process.env.API_URL
    if (!api_url) {
      throw new Error(
        "please specify the API_URL env var to, for example, http(s)://[IP]:[port]",
      )
    }
    server_cfg = {
      watch: {
        ignored: ['!**/node_modules/misirka/**'],
      },
      proxy: {
        "/ws": {
          target: api_url,
          ws: true,
          changeOrigin: true,
          secure: false,
          rewrite: (path: string) => path,
        },
      },
    }

    optimize_deps = {
      exclude: ['misirka'],
    }
  }

  const checker_cfg = {
    typescript: true,
  }

  return {
    optimizeDeps: optimize_deps,
    plugins: [viteSingleFile(), viteCompression(), checker(checker_cfg)],
    build: {
      assetsInlineLimit: Number.MAX_SAFE_INTEGER,
    },
    server: server_cfg,
  }
})
