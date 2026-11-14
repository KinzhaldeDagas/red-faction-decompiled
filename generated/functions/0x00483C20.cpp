// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483C20 rf_rfl_trigger_destroy_strings
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Thiscall trigger temporary destructor, no stack args. Destroys RFString at+108 then first RFString at+0; unwind also destroys first string if later destruction raises. No
// allocation free, target-array traversal, trigger deregistration, scalar reset or bitmap/sound release. Caller is RFL triggers loader on normal and unwind paths. Inherited SEH label
// mentioning Microsoft Concurrency/NumaInformation does not identify actual record semantics; original body is shared string-member destruction.
void __thiscall rf_rfl_trigger_destroy_strings(int this)
{
  rf_string_destroy_buffer((void *)(this + 108));
  rf_string_destroy_buffer((void *)this);
}

