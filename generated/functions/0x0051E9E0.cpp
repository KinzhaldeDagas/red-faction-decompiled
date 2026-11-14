// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051E9E0 rf_vector_component_address_unchecked
// UNREALRED VERIFIED [room-render-20261028]: Returns address this+4*signed index. Does not load component,clamp index or validate vector pointer. Negative/large indices accepted literally; return pointer may be outside object.
char *__thiscall rf_vector_component_address_unchecked(char *this, int a2)
{
  return this + 4 * a2;
}

