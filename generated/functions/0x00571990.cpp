// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571990 rf_rgba8_default_construct_noop
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Observed default color constructor used at blood-mark snapshot+14: returns this with no memory writes or calls. Does not initialize RGBA, whiten/clear color or validate packed color value.
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall default color constructor returns this with NO memory writes or calls. Does not initialize,clear or whiten RGBA. Multiple palette constructors only call this helper,so they likewise leave object memory untouched. Original generic library label replaced; existing observed blood-mark constructor contract retained.
void *__thiscall rf_rgba8_default_construct_noop(void *this)
{
  return this;
}

