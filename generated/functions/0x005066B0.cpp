// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005066B0 rf_trigger_destroy_embedded_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VClip initialization/preloads,byte occupancy and physical array sizes,trigger suppression/member cleanup and constructor ABI,original ECX/stack flow and PE bytes): Thiscall receiver,no stack arguments,void. Destroys pointer-array backing at trigger+724, RFString+692, then common-object embedded members through saved rf_common_object_destroy_embedded_members. SEH unwind tails retain the string/common cleanup order. Does not explicitly delete pointed-to link targets, unlink trigger ring, free whole trigger/sentinel storage or reset global trigger head. Static cleanup62F4A0 calls this on sentinel90B510. Member addresses verified from ECX adjustments, not a decompiler void-pointer element-size interpretation.
void __thiscall rf_trigger_destroy_embedded_members(void **this)
{
  rf_pointer_array_destroy_backing_storage(this + 181);
  rf_string_destroy_buffer(this + 173);
  rf_common_object_destroy_embedded_members((int)this);
}

