#import "@preview/cmarker:0.1.1": render

#set page(margin: (top: 1cm, bottom: 1cm, left: 1cm, right: 1cm))
#set text(size: 12pt)
#set par(leading: 0.4em)
#set list(spacing: 3pt)

#render(
  read("FOSDEM_Room_setup_checklist.md"),
  h1-level: 2,
  scope: (image: (source, alt: none, format: auto) => image(source, alt: alt, format: format))
)
