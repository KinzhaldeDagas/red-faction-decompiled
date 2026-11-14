// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004172E0 rf_clutter_runtime_construct_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Thiscall receiver,no stackargs. Calls common-object member constructor4129A0;then invalid4-byte timestamps676/688/692=-1,andemptyDWORD-array header704/708/712=0. Returnsreceiver. Commonbase writes only empty RFString24/28 and emptyphysics sphere-array388/392/396;vector/matrix/contact constructors are no-ops. Does NOT initialize class660/classIndex664/model128/voices672/720/SHORT724,all scalar lifetime/use fields or complete objectflags/pose. Runtime create supplies needed fields later. No owned outer allocation,virtualtable assignment or pointer guard here;normal/EHcleanup follows native constructors.
char *__thiscall rf_clutter_runtime_construct_members(char *this)
{
  rf_common_object_construct_members(this);
  rf_timestamp4_construct_invalid((int *)this + 169);
  rf_timestamp4_construct_invalid((int *)this + 172);
  rf_timestamp4_construct_invalid((int *)this + 173);
  rf_dword_array_construct_capacity(this + 704, 0);
  return this;
}

