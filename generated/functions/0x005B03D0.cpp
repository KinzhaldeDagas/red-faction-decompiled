// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B03D0 rf_ui_window_destroy_or_defer
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI window construction/navigation/parsing/drawing/cleanup, exact flag and list operations, original stack ABI and call sites): Thiscall no stack args. If global BYTE1CF7C24 nonzero,only sets window flags584 bit31 and returns without invalidating handles,unlinking or child cleanup. Otherwise invalidates handles via5AF480(no bitmap release),repeatedly removes flat-list head1204 until embedded sentinel592,repairs child prev608/next612 links and clears both. Reads child raw BYTE584; nonzero invokes child vtable0 then gadget deleting destructor5B11C0(flags1),zero invokes child vtable0 only. Raw indirect calls have NO pushed stack args; extra decompiler arguments are inference residue. If window next1252 nonNULL,repairs global window previous/next links and zeros1252/1256. Finally destroys base auxiliary recordsthrough the
// existing base auxiliary-list destructor. Does not delete window allocation,reset tree/selection fields or clear deferred bit. Return differs by path and is not uniform success boolean.
_DWORD *__thiscall rf_ui_window_destroy_or_defer(_DWORD *this)
{
  _DWORD *v2; // [esp+0h] [ebp-14h]
  _DWORD *v4; // [esp+10h] [ebp-4h]

  if ( unk_1CF7C24 )
  {
    *(this + 146) |= 0x80000000;
    return this;
  }
  else
  {
    rf_ui_window_invalidate_bitmap_handles(this);
    while ( (_DWORD *)*(this + 301) != this + 148 )
    {
      v4 = (_DWORD *)*(this + 301);
      *(_DWORD *)(v4[152] + 612) = v4[153];
      *(_DWORD *)(v4[153] + 608) = v4[152];
      v4[153] = 0;
      v4[152] = 0;
      if ( rf_ui_gadget_get_raw_flag_byte_584(v4) )
      {
        (*(void (__thiscall **)(_DWORD *))*v4)(v4);
        if ( v4 )
          v2 = rf_ui_gadget_scalar_deleting_destructor_5b11c0(v4, 1);
        else
          v2 = nullptr;
      }
      else
      {
        (*(void (__thiscall **)(_DWORD *, _DWORD *))*v4)(v4, v2);
      }
    }
    if ( *(this + 313) )
    {
      *(_DWORD *)(*(this + 314) + 1252) = *(this + 313);
      *(_DWORD *)(*(this + 313) + 1256) = *(this + 314);
      *(this + 313) = 0;
      *(this + 314) = 0;
    }
    return (_DWORD *)rf_ui_base_destroy_auxiliary_records((int)this);
  }
}

