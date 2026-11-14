// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1080 rf_ui_base_initialize_rect
// UNREALRED VERIFIED [ui-properties-20261029]: Arguments base kind,x,y,width,height,ID. Negative ID replaced by current counter0x664B2C then counter decremented;if new counter>0,resets counter=-1. Stores kind+8,x+12,y+16,w+20,h+24,ID+288. Clears bytes+28,+29,+30 and callback DWORD+580,reinitializes auxiliary sentinel+292/+296,sets live BYTE+4=1,returns this. No dimension validation,ID collision check or destruction of prior auxiliary records before resetting links.
int __thiscall rf_ui_base_initialize_rect(int this, int a2, int a3, int a4, int a5, int a6, int a7)
{
  if ( a7 < 0 )
  {
    a7 = dword_664B2C--;
    if ( dword_664B2C > 0 )
      dword_664B2C = -1;
  }
  *(_DWORD *)(this + 8) = a2;
  *(_DWORD *)(this + 12) = a3;
  *(_DWORD *)(this + 16) = a4;
  *(_DWORD *)(this + 20) = a5;
  *(_DWORD *)(this + 24) = a6;
  *(_DWORD *)(this + 288) = a7;
  *(_BYTE *)(this + 30) = 0;
  *(_DWORD *)(this + 580) = 0;
  *(_BYTE *)(this + 29) = 0;
  *(_BYTE *)(this + 28) = 0;
  *(_DWORD *)(this + 292) = this + 292;
  *(_DWORD *)(this + 296) = this + 292;
  *(_BYTE *)(this + 4) = 1;
  return this;
}

