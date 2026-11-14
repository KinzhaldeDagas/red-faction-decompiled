// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EED20 rf_text_list_initialize_attached_scrollbar
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): This derived scrollbar684bytes;args parent list,horizontalBYTE,thickness,id,flagsBYTE,raw base flag. Gets parent owner. Horizontal base geometry x0,y=parentH+1,w=parentW,h=thickness;vertical x=parentW+1,y0,w=thickness,h=parentH. Calls slider initialize with thumbLength=thickness,positionCount20;reparents. Horizontal writes parent barH788=this,extra pageExtent680=parent innerW,content=contentW;vertical writes barV784=this,pageExtent=innerH,content=contentH. Sets range648=content-pageExtent+1,pageStep660=pageExtent,then recomputes thumb length. No guards for missing parent/zero extents/nonpositive range,previous scrollbar replacement or position clamp.
_DWORD *__thiscall rf_text_list_initialize_attached_scrollbar(
        int *this,
        _DWORD *a2,
        char a3,
        int a4,
        int a5,
        char a6,
        char a7)
{
  int content_width; // eax
  int owner_window; // [esp+4h] [ebp-14h]
  int v11; // [esp+8h] [ebp-10h] BYREF
  int v12; // [esp+Ch] [ebp-Ch] BYREF
  int v13; // [esp+10h] [ebp-8h] BYREF
  int v14; // [esp+14h] [ebp-4h] BYREF

  owner_window = rf_ui_gadget_get_owner_window(a2);
  if ( a3 )
  {
    v11 = 0;
    v13 = a4;
    rf_ui_base_get_size(a2, &v14, &v12);
    ++v12;
  }
  else
  {
    v12 = 0;
    v14 = a4;
    rf_ui_base_get_size(a2, &v11, &v13);
    ++v11;
  }
  rf_ui_slider_initialize((int)this, owner_window, v11, v12, v14, v13, a3, a4, 20, a5, a6, a7);
  rf_ui_gadget_set_parent(this, (int)a2);
  if ( a3 )
  {
    a2[197] = this;
    *(this + 170) = rf_text_list_inner_width(a2);
    content_width = rf_text_list_get_content_width(a2);
  }
  else
  {
    a2[196] = this;
    *(this + 170) = rf_text_list_inner_height(a2);
    content_width = rf_text_list_get_content_height(a2);
  }
  *(this + 162) = content_width - *(this + 170) + 1;
  rf_ui_slider_set_page_step(this, *(this + 170));
  return rf_scrollbar_recompute_thumb_length((int)this);
}

