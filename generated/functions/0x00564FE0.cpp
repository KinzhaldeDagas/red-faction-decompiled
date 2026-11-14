// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00564FE0 rf_model_animation_duration_seconds
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] Animation-duration cdecl adapter: accepts model descriptor pointer and animation index, passes descriptor in ECX plus stacked index to 0x562CF0, and returns its x87 ST(0) unchanged. Speech scheduler 0x42BBB0 and AI action43 path 0x40DA16 consume ST(0) with FSTP. Auto-inferred void/integer pseudocode return types can hide the result; assembly establishes floating duration flow. No type mutation is made by this decode.
double __cdecl rf_model_animation_duration_seconds(unsigned int *model, int animation)
{
  return rf_model_animation_duration_by_kind(model, animation);
}

