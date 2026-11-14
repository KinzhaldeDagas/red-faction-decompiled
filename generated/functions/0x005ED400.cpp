// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED400 rf_dsound3d_initialize_with_optional_property_check
// UNREALRED VERIFIED [wave-codec-20261028]: If ready byte0x1F670FC==1,returns0. Argument exactly1 requires property interface0x5913D0 nonnull,QuerySupport vtable+20(GUID0x664AFC,property0),nonnegative result and support mask2 present. Then vtable+16 Set(GUID,property0,instance0,size0,input DWORD1,length4); negative result-1. Other argument values skip property operations. Calls0x5ED4E0 to obtain listener; failure-1,success ready1,return0. Does not roll back property operations. The property call sends input DWORD1; it does not retrieve data or return an output length.
int __cdecl rf_dsound3d_initialize_with_optional_property_check(char a1)
{
  int v2; // [esp+4h] [ebp-Ch] BYREF
  int property_interface_pointer; // [esp+8h] [ebp-8h]
  int v4; // [esp+Ch] [ebp-4h] BYREF

  if ( byte_1F670FC[0] == 1 )
    return 0;
  if ( a1 != 1 )
    goto LABEL_17;
  property_interface_pointer = rf_dsound_get_property_interface_pointer();
  if ( !property_interface_pointer )
    return -1;
  v2 = 0;
  if ( (*(int (__stdcall **)(int, void *, _DWORD, int *))(*(_DWORD *)property_interface_pointer + 20))(
         property_interface_pointer,
         &unk_664AFC,
         0,
         &v2) < 0 )
    return -1;
  if ( (v2 & 2 | 1) != 3 )
    return -1;
  v4 = 1;
  if ( (*(int (__stdcall **)(int, void *, _DWORD, _DWORD, _DWORD, int *, int))(*(_DWORD *)property_interface_pointer + 16))(
         property_interface_pointer,
         &unk_664AFC,
         0,
         0,
         0,
         &v4,
         4) < 0 )
    return -1;
LABEL_17:
  if ( rf_dsound3d_query_primary_listener_interface() )
    return -1;
  byte_1F670FC[0] = 1;
  return 0;
}

