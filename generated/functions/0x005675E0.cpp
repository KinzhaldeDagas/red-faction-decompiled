// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005675E0 rf_float_to_int_truncate_stdcall
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): stdcall(float),RET4. Converts to signed int32 through native compiler float-to-int helper,with truncation toward0 for ordinary finite in-range inputs. No0.5 addition,range clamp,finite test or output pointer; exceptional conversion follows helper behavior.
int __stdcall rf_float_to_int_truncate_stdcall(float x)
{
  return (int)x;
}

