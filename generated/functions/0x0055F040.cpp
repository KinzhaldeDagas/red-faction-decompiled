// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F040 rf_replicator_has_elapsed
// UNREALRED VERIFIED [combat-clock-20260930] Unarmed negative deadline returns false. Armed deadline is compared to game clock0x663E90 with the536400000 ms half-period test. Fire owner0x431FD0 checks this helper for its ordinary fire timer. This does not establish RF packet serialization of timestamps; Unreal synchronized server-time mapping is an explicit host adaptation.
// UNREALRED VERIFIED [mission-protection-20261020] Protection update0x500890 only queries this predicate: it does not reset. Expiry is persistent until changed, with period1072800000 and half-period536400000 milliseconds. Do not substitute a one-shot timer callback or remove the expired protection record.
// UNREALRED VERIFIED [trigger-inside-time-20261021] InsideTime uses this wrapped half-period comparison on each current admitted query, then resets the embedded timer BEFORE activation attempt. Expiry is not an asynchronous callback and cannot fabricate an activator or a Use mode.
// UNREALRED VERIFIED [clutter-clock-20261029] Clutter class50ms and object75ms expiry use the common game clock with persistent elapsed status and wrapped half-period comparison. A wall-time callback while the imported simulation is paused is not this contract.
bool __thiscall rf_replicator_has_elapsed(int *this)
{
  if ( *this < 0 )
    return 0;
  if ( *this <= dword_663E90 )
    return dword_663E90 - *this <= 536400000;
  return *this - dword_663E90 > 536400000;
}

