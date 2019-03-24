set(OUTPUT base58)

set(OUTPUT_SOURCES
  base58.c
  main.c)

add_executable(${OUTPUT}
  ${OUTPUT_SOURCES})
