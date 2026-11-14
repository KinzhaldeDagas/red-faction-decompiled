// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A69D0 rf_text_list_initialize
// UNREALRED VERIFIED [list-selection-20261029]: Thiscall list plus10 stack arguments. Delegates UI creation0x5AB1A0 with fixed type8 and supplied parent/geometry/options. Stores flags from argument10 at+628,configured wrap width arg7+672,height cap arg8+676;zeros scroll+708/+712 and content extents+680/+684,selected-state BYTE+688,search count+664,bar pointers+784/+788. Sets DWORD+696=-1,paddings+700/+704=2,entry gap+716=2,horizontal step+720=10,style pointer+792=0x1CF7BE0,deadline+668=current clock via offset0. Flag2 allocates684-byte scrollbar,constructs0x5A96A0,creates vertical via0x5EED20 orientation0;flag4 analogous horizontal orientation1. Both set child BYTE+584=1. No allocation failure guard before child use,entry-list clearing or direct old-bar destruction in body. Return is branch-dependent flags/helper/child pointer,not consistently this.
_DWORD *__thiscall rf_text_list_initialize(
        int this,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        char a11)
{
  _DWORD *result; // eax
  _DWORD *v12; // [esp+4h] [ebp-2Ch]
  _DWORD *v13; // [esp+8h] [ebp-28h]
  _DWORD *v15; // [esp+10h] [ebp-20h]
  _DWORD *v16; // [esp+18h] [ebp-18h]

  rf_ui_gadget_initialize(this, a2, 8, a3, a4, a5, a6, a9, a11);
  *(_DWORD *)(this + 696) = -1;
  *(_DWORD *)(this + 628) = a10;
  *(_DWORD *)(this + 672) = a7;
  *(_DWORD *)(this + 676) = a8;
  *(_DWORD *)(this + 708) = 0;
  *(_DWORD *)(this + 712) = 0;
  *(_DWORD *)(this + 680) = 0;
  *(_DWORD *)(this + 684) = 0;
  *(_BYTE *)(this + 688) = 0;
  *(_DWORD *)(this + 700) = 2;
  *(_DWORD *)(this + 704) = 2;
  *(_DWORD *)(this + 716) = 2;
  *(_DWORD *)(this + 720) = 10;
  *(_DWORD *)(this + 792) = &unk_1CF7BE0;
  *(_DWORD *)(this + 664) = 0;
  rf_clock_deadline_set_wrapped_offset((int *)(this + 668), 0);
  *(_DWORD *)(this + 784) = 0;
  *(_DWORD *)(this + 788) = 0;
  result = (_DWORD *)(a10 & 2);
  if ( (a10 & 2) != 0 )
  {
    v16 = operator new(0x2ACu);
    if ( v16 )
      v13 = rf_ui_scrollbar_construct(v16);
    else
      v13 = nullptr;
    result = (_DWORD *)rf_text_list_initialize_attached_scrollbar(v13, this, 0, 11, -1, 1, 0);
    *((_BYTE *)v13 + 584) = 1;
  }
  if ( (a10 & 4) != 0 )
  {
    v15 = operator new(0x2ACu);
    if ( v15 )
      v12 = rf_ui_scrollbar_construct(v15);
    else
      v12 = nullptr;
    rf_text_list_initialize_attached_scrollbar(v12, this, 1, 11, -1, 1, 0);
    *((_BYTE *)v12 + 584) = 1;
    return v12;
  }
  return result;
}

