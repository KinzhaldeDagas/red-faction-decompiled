// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00586890 rf_character_instance_advance_animations
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, character state/action time advancement, hold/event/ownership edges, AABB support/corner math, sort comparator and original x87/stack ABI): Thiscall receiver,deltaSeconds float plus TWO UNUSED stack DWORDs,RET12; EAX returns receiver,not status. Early no-op if hold BYTE7500 nonzero,record count4816<1,or base7504 clip count3928 zero. Otherwise increments WORD7416(wrapping16-bit),deltaTick=ftol(deltaSeconds*30.0*160.0),resets strongest-state record7496=-1. Active records12 bytes at4820:animation index0,current integer tick4,mix float8. State classification is ANY nonzero base BYTE[4620+resolvedAnimationIndex]. For every record computes signed duration=end-start. Across state records accumulates float sumInverseDurationMix=sum(mix/duration) and sumMix; chooses first strictly greatest ORDERED positive mix for7496(initial
// max0). No duration-zero,count/clip/buffer/index/finite/negative-time guard; normal insertion elsewhere caps records16,but this function does not enforce that cap. If state sumMix compares exactly zero,resets phase7428=0 and advances only non-state records with nonzero mix by deltaTick; does NOT select/recompare animation-alone owner7424 in this branch. Otherwise divides accumulated inverse-duration sum by sumMix,adds deltaTick*rate to float phase7428,repeatedly subtracts1 while phase>=1,and records only a boolean that any wrap occurred. No wrap for negative phase,no iteration/progress cap; +infinity or sufficiently large float values that stop changing on subtract1 can loop indefinitely. Raw loop TEST AH,1 rejects unordered,so NaN phase exits loop. For each state record with nonzero mix sets tick=start+ftol(floor(float(duration*phase))); zero-mix state ticks stay unchanged. For selected
// strongest state7496 only,tests2 marker ticks at resolved RFA object+80/+100 using exact conditions(newTick>=marker && marker>oldTick) OR(wrapped && marker>oldTick) OR(wrapped && marker<newTick); sets instance BYTE7492/7493=1 when crossed. Does NOT clear event bytes here,retain wrap count or test other states markers. Non-state nonzero-mix records add deltaTick. In nonzero-state-sum branch only,first action becomes owner7424 when owner==-1; owner change zeros floats7448/7452. Otherwise compares root-track weights sampled5BA560 at updated ticks,using track index base+6740; candidate strictly greater ORDERED curve weight replaces incumbent. Mix is only a nonzero gate and is NOT multiplied into that comparison. Candidate bypass-ramp byte is indexed by CURRENT RECORD POSITION k at base4620+k,whereas incumbent bypass byte uses its resolved animation index: raw586DD6/586E2C confirm asymmetry.
// No owner-index validity check. Next pass checks ALL non-state records regardless of mix: if current tick>=authored end and record index==freeze designation7420,clamps EXACT end and sets global hold BYTE7500=1; other completed records clamp end and set mix0. If a retiring record is owner7424,also sets owner=-1,zeros7448/7452,clearsBYTE7444,zeros vectors7456/7468. The current call still processes remaining records after setting hold; subsequent calls stop at entry. Final loop removes EVERY record whose mix equals0,including states,via exact animation-index remover5873C0; remover compacts12-byte records and adjusts tracked indices7420/7424/7496,so loop rechecks same slot after removal. No semantic action priority,hold-last offset(end-1),mix ramp update or rollback. Existing repeatable summary retained.
// UNREALRED VERIFIED [combat-speech-eye-phase-20261111]: One-positive-canonical-state specialization for setup: deltaTick=trunc(double(dt)*30*160); reciprocal-duration accumulation rounds through binary32, rate divide by sumMix roundsbinary32; phase=float(double(deltaTick)*rate+oldPhase), repeated float(phase-1) wraps; selected tick=start+floor(float(double(signed duration)*phase)). Finaltwo stackDWORDs are UNUSED, so lastarg1 in42E5B8 is not an evaluation-only clock gate. Host nonfinite/overflow/nonprogress domains must be explicit, not clamped.
int __thiscall rf_character_instance_advance_animations(int this, float a2, int a3, int a4)
{
  int result; // eax
  int end_tick; // esi
  int start_tick; // eax
  int v7; // esi
  int v8; // esi
  int v9; // esi
  int v10; // eax
  float *v11; // eax
  int v12; // eax
  double v13; // [esp+10h] [ebp-32Ch]
  float value; // [esp+18h] [ebp-324h]
  float v16[3]; // [esp+24h] [ebp-318h] BYREF
  float copy_result[3]; // [esp+30h] [ebp-30Ch] BYREF
  float v18[3]; // [esp+3Ch] [ebp-300h] BYREF
  int v19; // [esp+48h] [ebp-2F4h]
  int v20; // [esp+4Ch] [ebp-2F0h]
  int j; // [esp+50h] [ebp-2ECh]
  int v22; // [esp+54h] [ebp-2E8h]
  int m; // [esp+58h] [ebp-2E4h]
  int v24; // [esp+5Ch] [ebp-2E0h]
  int v25; // [esp+60h] [ebp-2DCh]
  int k; // [esp+64h] [ebp-2D8h]
  char v27; // [esp+6Bh] [ebp-2D1h]
  int v28; // [esp+6Ch] [ebp-2D0h]
  int v29; // [esp+70h] [ebp-2CCh]
  _DWORD v30[173]; // [esp+74h] [ebp-2C8h]
  float v31; // [esp+328h] [ebp-14h]
  float v32; // [esp+32Ch] [ebp-10h]
  int i; // [esp+330h] [ebp-Ch]
  int v34; // [esp+334h] [ebp-8h]
  float v35; // [esp+338h] [ebp-4h]

  result = this;
  if ( !*(_BYTE *)(this + 7500) && *(int *)(this + 4816) >= 1 )
  {
    result = this;
    if ( *(_DWORD *)(*(_DWORD *)(this + 7504) + 3928) )
    {
      ++*(_WORD *)(this + 7416);
      v29 = (int)(a2 * 30.0 * 160.0);
      v34 = *(_DWORD *)(this + 7504) + 3932;
      *(_DWORD *)(this + 7496) = -1;
      v31 = 0.0;
      v32 = 0.0;
      v35 = 0.0;
      for ( i = 0; i < *(_DWORD *)(this + 4816); ++i )
      {
        v28 = *(_DWORD *)(this + 12 * i + 4820);
        end_tick = rf_rfa_get_end_tick(*(void **)(v34 + 4 * v28));
        start_tick = rf_rfa_get_start_tick(*(void **)(v34 + 4 * v28));
        v30[i] = end_tick - start_tick;
        if ( *(_BYTE *)(*(_DWORD *)(this + 7504) + v28 + 4620) )
        {
          v32 = 1.0 / (double)(int)v30[i] * *(float *)(this + 12 * i + 4828) + v32;
          v35 = v35 + *(float *)(this + 12 * i + 4828);
          if ( v31 < (double)*(float *)(this + 12 * i + 4828) )
          {
            *(_DWORD *)(this + 7496) = i;
            v31 = *(float *)(this + 12 * i + 4828);
          }
        }
      }
      if ( v35 == 0.0 )
      {
        *(float *)(this + 7428) = 0.0;
        for ( j = 0; j < *(_DWORD *)(this + 4816); ++j )
        {
          v20 = *(_DWORD *)(this + 12 * j + 4820);
          if ( !*(_BYTE *)(*(_DWORD *)(this + 7504) + v20 + 4620) && *(float *)(this + 12 * j + 4828) != 0.0 )
            *(_DWORD *)(this + 12 * j + 4824) += v29;
        }
      }
      else
      {
        v32 = v32 / v35;
        *(float *)(this + 7428) = (double)v29 * v32 + *(float *)(this + 7428);
        v27 = 0;
        while ( *(float *)(this + 7428) >= 1.0 )
        {
          *(float *)(this + 7428) = *(float *)(this + 7428) - 1.0;
          v27 = 1;
        }
        for ( k = 0; k < *(_DWORD *)(this + 4816); ++k )
        {
          v25 = *(_DWORD *)(this + 12 * k + 4820);
          if ( *(_BYTE *)(*(_DWORD *)(this + 7504) + v25 + 4620) )
          {
            v24 = *(_DWORD *)(this + 12 * k + 4824);
            if ( *(float *)(this + 12 * k + 4828) != 0.0 )
            {
              v7 = rf_rfa_get_end_tick(*(void **)(v34 + 4 * v25));
              value = (double)(v7 - rf_rfa_get_start_tick(*(void **)(v34 + 4 * v25))) * *(float *)(this + 7428);
              v8 = (int)rf_floor_float(value);
              *(_DWORD *)(this + 12 * k + 4824) = rf_rfa_get_start_tick(*(void **)(v34 + 4 * v25)) + v8;
            }
            if ( k == *(_DWORD *)(this + 7496) )
            {
              for ( m = 0; m < 2; ++m )
              {
                if ( *(_DWORD *)(this + 12 * k + 4824) >= *(_DWORD *)(*(_DWORD *)(v34 + 4 * v25) + 20 * m + 80)
                  && *(_DWORD *)(*(_DWORD *)(v34 + 4 * v25) + 20 * m + 80) > v24
                  || v27 && *(_DWORD *)(*(_DWORD *)(v34 + 4 * v25) + 20 * m + 80) > v24
                  || v27 && *(_DWORD *)(*(_DWORD *)(v34 + 4 * v25) + 20 * m + 80) < *(_DWORD *)(this + 12 * k + 4824) )
                {
                  *(_BYTE *)(m + this + 7492) = 1;
                }
              }
            }
          }
          else if ( *(float *)(this + 12 * k + 4828) != 0.0 )
          {
            *(_DWORD *)(this + 12 * k + 4824) += v29;
            if ( *(_DWORD *)(this + 7424) == -1 )
            {
              *(float *)(this + 7448) = 0.0;
              *(float *)(this + 7452) = *(float *)(this + 7448);
              *(_DWORD *)(this + 7424) = k;
            }
            else
            {
              v22 = *(_DWORD *)(this + 12 * *(_DWORD *)(this + 7424) + 4820);
              v13 = rf_rfa_track_weight_at_time(
                      (void *)*(_DWORD *)(v34 + 4 * v25),
                      *(_DWORD *)(*(_DWORD *)(this + 7504) + 6740),
                      *(_DWORD *)(this + 12 * k + 4824),
                      *(_BYTE *)(*(_DWORD *)(this + 7504) + k + 4620));
              if ( rf_rfa_track_weight_at_time(
                     (void *)*(_DWORD *)(v34 + 4 * v22),
                     *(_DWORD *)(*(_DWORD *)(this + 7504) + 6740),
                     *(_DWORD *)(this + 12 * *(_DWORD *)(this + 7424) + 4824),
                     *(_BYTE *)(*(_DWORD *)(this + 7504) + v22 + 4620)) < v13 )
              {
                *(float *)(this + 7448) = 0.0;
                *(float *)(this + 7452) = *(float *)(this + 7448);
                *(_DWORD *)(this + 7424) = k;
              }
            }
          }
        }
      }
      for ( i = 0; i < *(_DWORD *)(this + 4816); ++i )
      {
        v19 = *(_DWORD *)(this + 12 * i + 4820);
        if ( !*(_BYTE *)(*(_DWORD *)(this + 7504) + v19 + 4620) )
        {
          v9 = 12 * i;
          if ( *(_DWORD *)(this + v9 + 4824) >= rf_rfa_get_end_tick(*(void **)(v34 + 4 * v19)) )
          {
            if ( i == *(_DWORD *)(this + 7420) )
            {
              v10 = rf_rfa_get_end_tick(*(void **)(v34 + 4 * v19));
              *(_DWORD *)(this + 12 * i + 4824) = v10;
              *(_BYTE *)(this + 7500) = 1;
            }
            else
            {
              if ( i == *(_DWORD *)(this + 7424) )
              {
                *(_DWORD *)(this + 7424) = -1;
                *(float *)(this + 7448) = 0.0;
                *(float *)(this + 7452) = *(float *)(this + 7448);
                *(_BYTE *)(this + 7444) = 0;
                v11 = rf_vector3_set_components_return_destination(v18, 0.0, 0.0, 0.0);
                rf_vector_copy((float *)(this + 7456), copy_result, v11);
                rf_vector_copy((float *)(this + 7468), v16, (const float *)(this + 7456));
              }
              *(float *)(this + 12 * i + 4828) = 0.0;
              v12 = rf_rfa_get_end_tick(*(void **)(v34 + 4 * v19));
              *(_DWORD *)(this + 12 * i + 4824) = v12;
            }
          }
        }
      }
      i = 0;
      while ( 1 )
      {
        result = this;
        if ( i >= *(_DWORD *)(this + 4816) )
          break;
        if ( *(float *)(this + 12 * i + 4828) == 0.0 )
          rf_character_instance_remove_action_record((_DWORD *)this, *(_DWORD *)(this + 12 * i + 4820));
        else
          ++i;
      }
    }
  }
  return result;
}

