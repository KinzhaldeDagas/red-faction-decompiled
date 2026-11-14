// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4550 rf_fmod_float_wrapper
// UNREALRED VERIFIED [texture-upload-20261028]: Directtwo-floatwrapperaround0x5E4570,__CIfmod-basedremainder. Prior _hypotf_1 librarynamewasfalse; texelsamplercallswithsecondargument1.0towrapUV. Returnsfloatresultinx87,notpointer.
float __cdecl rf_fmod_float_wrapper(float X, float Y)
{
  return rf_fmod_float_via_x87_intrinsic(X, Y);
}

