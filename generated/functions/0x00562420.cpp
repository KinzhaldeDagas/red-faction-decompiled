// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562420 rf_model_handle_get_bounds_sphere
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Corrected false fastcall signature to ECX handle plus(outCenter,outRadius), RET8. Calls562440(handle,index-1,outputs). Incoming EDX is not an argument. No independent initialization, status or validation.
void __thiscall rf_model_handle_get_bounds_sphere(void *this, float *a2, float *a3)
{
  rf_model_handle_get_indexed_bounds_sphere(this, -1, a2, a3);
}

