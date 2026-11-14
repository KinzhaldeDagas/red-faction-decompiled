// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561B70 rf_model_render_options_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Runs no-op RGBA default constructors at12,24,40 and no-op matrix row constructor at44, then561BC0 defaults. Record extends through79. Color bytes12..15,24..27,40..43 remain uninitialized; no blanket memset or opaque-white initialization. Used by corpse/item/weapon/model render callers. Returns receiver.
char *__thiscall rf_model_render_options_construct(char *this)
{
  rf_rgba8_default_construct_noop(this + 12);
  rf_rgba8_default_construct_noop(this + 24);
  rf_rgba8_default_construct_noop(this + 40);
  rf_matrix3_construct(this + 44);
  rf_model_render_options_reset_defaults(this);
  return this;
}

