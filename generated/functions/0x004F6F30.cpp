// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F6F30 rf_quickload_request
// UNREALRED VERIFIED [save-validation-20261028]: Sets pending load byte0x894D2A=1 only when multiplayer-runtime mode is zero. Return is multiplayer-mode value: zero can mean request accepted, not boolean failure. File validation is deferred.
int rf_quickload_request()
{
  int result; // eax

  result = rf_multiplayer_runtime_mode;
  if ( !rf_multiplayer_runtime_mode )
    unk_894D2A = 1;
  return result;
}

