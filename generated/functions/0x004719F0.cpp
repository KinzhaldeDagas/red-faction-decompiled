// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004719F0 rf_ui_slider_set_value_clamped
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): Thiscall sliderECX,float value stack,RET4. x87 load/store argument into float52 FIRST,then
// float_clamp_in_place(&float52,minFLOAT64,maxFLOAT68). No callback,sound,normalized-fraction conversion,enabled-state check,range reordering or explicit finite validation. Clamp
// helper owns unordered/reversed-bound behavior. Value is raw slider range value,not necessarily0..1.
void __thiscall rf_ui_slider_set_value_clamped(float *this, float a2)
{
  *(this + 13) = a2;
  rf_float_clamp_in_place(this + 13, *(this + 16), *(this + 17));
}

