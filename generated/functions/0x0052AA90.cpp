// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052AA90 rf_renderer_light_record268_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, Boolean stage dispatch and workspace ownership,class bits/action table,transforms and room-return ABI,original ECX/stack flow and PE bytes): Thiscall receiver plainRET returns self. Calls no-op vector constructors at12,24,36,92,104,116, then vector-constructor iterator for6 entries stride16 starting148 with no-op prefix constructor. These calls do not initialize light type,links,range,RGB,flags,selectors or plane scalar components. No whole-record memset or allocation; semantic use is268-byte renderer-light record construction, not Boolean workspace setup.
char *__thiscall rf_renderer_light_record268_construct_noop(char *this)
{
  rf_vector3_default_construct_noop(this + 12);
  rf_vector3_default_construct_noop(this + 24);
  rf_vector3_default_construct_noop(this + 36);
  rf_vector3_default_construct_noop(this + 92);
  rf_vector3_default_construct_noop(this + 104);
  rf_vector3_default_construct_noop(this + 116);
  rf_vector_construct_no_unwind(this + 148, 0x10u, 6, rf_vector_prefix_construct_noop);
  return this;
}

