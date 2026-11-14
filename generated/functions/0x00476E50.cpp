// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476E50 rf_cutscene_aux_bezier_record_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): Native thiscall ECX record, no stack arguments, returns original record. Constructs empty RFString at+0, then cubic-Bezier embedded
// controls at+8 via5A4540. SEH cleanup destroys RFString if later construction unwinds. Does not set final identifier/scalars, allocate record storage or install a vtable. Paired
// destructor476EB0 and static cleanup62EF20 establish an array of32 records,100-byte stride at6FB670. Former Concurrency NumaInformation name, receiver type and library flag are
// false; primitive receiver prototype corrected without changing local types or code.
void *__thiscall rf_cutscene_aux_bezier_record_construct(void *this)
{
  rf_string_construct_empty(this);
  rf_cubic_bezier_construct_embedded_controls((_DWORD *)this + 2);
  return this;
}

