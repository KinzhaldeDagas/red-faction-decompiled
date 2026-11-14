// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00486E80 sub_486E80
// UNREALRED VERIFIED [ai-health-goals-20261028] Per-level initialization0x448190 calls this at0x44823E to reset named waypoint-list count0x700478 to0. Existing allocated string/record storage is not destroyed here; process teardown0x486E40/0x62F080 handles separate string/destructor cleanup.
int sub_486E80()
{
  unk_700478 = 0;
  return 0;
}

