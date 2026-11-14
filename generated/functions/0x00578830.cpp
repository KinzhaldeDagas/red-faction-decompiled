// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00578830 rf_memory_text_parser_destroy_buffer_adapter
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitmap records/animation rates, decoded-handle tag test, tile descriptor offsets and text-parser ownership): ECX receiver,no stack args. Calls579190 close-buffer helper and returns its receiver pointer. Adds no filename/cursor/field reset and does not free receiver object. Close helper frees only when buffer nonNULL AND global189745C==0,then clears buffer0 regardless.
void **__thiscall rf_memory_text_parser_destroy_buffer_adapter(void **this)
{
  return rf_memory_text_parser_close_buffer(this);
}

