// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED3D0 rf_dsound3d_release_listener_interface
// UNREALRED VERIFIED [wave-codec-20261028]: If listener0x1F670F8 nonnull,calls Release vtable+8 then nulls it. Does not change ready byte. Return Release count when called; uninitialized/incidental return on null path.
int rf_dsound3d_release_listener_interface()
{
  int result; // eax

  if ( dword_1F670F8 )
  {
    result = (*(int (__stdcall **)(_DWORD *))(*dword_1F670F8 + 8))(dword_1F670F8);
    dword_1F670F8 = nullptr;
  }
  return result;
}

