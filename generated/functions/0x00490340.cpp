// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490340 rf_text_file_scalar_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Calls text-file destructor5BBB80 to fclose/free members without clearing them. Flag byte bit1 additionally operator deletes containing object; returns original receiver bits even if freed. Other flags ignored; no vector-array cookie behavior or destructor-status propagation.
void *__thiscall rf_text_file_scalar_deleting_destructor(void *this, char a2)
{
  rf_text_file_destroy((int)this);
  if ( (a2 & 1) != 0 )
    operator delete(this);
  return this;
}

