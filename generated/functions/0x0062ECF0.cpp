// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062ECF0 rf_chat_input_string_atexit_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, chat input/console call chains, native500ms throttle, exact key predicates, original key maps/level prefixes,
// RFString ownership and static registration boundaries): Noarg. Pass ECX=&RFString6F2CDC to string_destroy_buffer and return;existing definition/type unchanged. Registered with
// atexit by recovered62AA90. Releases owned edit-string buffer only;does not clear active/init/mode,reset throttle or send. Original native body conventional
// frame,movECX,call,pop,RET;no additional cleanup delegates.
void rf_chat_input_string_atexit_destroy()
{
  rf_string_destroy_buffer(unk_6F2CDC);
}

