// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6F10 rf_quicksave_request
// UNREALRED VERIFIED [save-validation-20261028]: Calls0x4F6F50 eligibility predicate; on true sets pending save byte0x894D29=1. Returns predicate result; execution is deferred to quick-action pump.
int __thiscall rf_quicksave_request(void *this)
{
  int result; // eax

  result = (unsigned __int8)rf_quicksave_is_allowed(this);
  if ( (_BYTE)result )
    unk_894D29 = 1;
  return result;
}

