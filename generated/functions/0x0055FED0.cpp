// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055FED0 rf_string_trim_space_tab_lf_both_ends
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Calls trailing trim then leading trim helpers, in that order. Their trim set is space,tab,LF only; CR and other whitespace not handled here. Returns leading helper result. No separate repair of stale positive extent/null-buffer state from underlying release/trim paths.
int __thiscall rf_string_trim_space_tab_lf_both_ends(void *this)
{
  rf_string_trim_trailing_space_tab_lf((int)this);
  return rf_string_trim_leading_space_tab_lf((int)this);
}

