// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471930 rf_ui_slider_update_value_from_pointer
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): ECX slider,stack(x,y),RET8. OrientationBYTE40 ANY nonzero uses y/scaleY then round tofloat,floor helper,subtract
// absoluteY,divide by signed heightDWORD24;zero uses x/scaleX,absoluteX,widthDWORD20. Round normalized fraction tofloat,delegate clamp0..1,then store
// float52=minFLOAT64+(maxFLOAT68-min64)*fraction. No scale/dimension zero,finite,pointer,state/enabled checks or callbacks/sounds;does not snap to discrete steps. Existing returnint
// is incidentalEAX,not a float/status.
int __thiscall rf_ui_slider_update_value_from_pointer(int this, int a2, int a3)
{
  float v4; // [esp+Ch] [ebp-1Ch]
  float value; // [esp+14h] [ebp-14h]
  float v7; // [esp+1Ch] [ebp-Ch]
  float v8; // [esp+20h] [ebp-8h]
  int v9; // [esp+24h] [ebp-4h] BYREF

  if ( *(_BYTE *)(this + 40) )
  {
    value = (double)a3 / rf_ui_scale_y;
    v8 = rf_floor_float(value);
    *(float *)&v9 = (v8 - (double)rf_ui_control_absolute_y((_DWORD *)this)) / (double)*(int *)(this + 24);
  }
  else
  {
    v4 = (double)a2 / rf_ui_scale_x;
    v7 = rf_floor_float(v4);
    *(float *)&v9 = (v7 - (double)rf_ui_control_absolute_x((_DWORD *)this)) / (double)*(int *)(this + 20);
  }
  rf_float_clamp_in_place((float *)&v9, 0.0, 1.0);
  *(float *)(this + 52) = (*(float *)(this + 68) - *(float *)(this + 64)) * *(float *)&v9 + *(float *)(this + 64);
  return this;
}

