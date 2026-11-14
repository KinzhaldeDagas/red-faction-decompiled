// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CB40 rf_plane_point_signed_distance
// UNREALRED VERIFIED [mission-unhide-20261020] Returns float(dot(point,plane.normal)+plane.distance). Paired with569600 this establishes start-side and direction for UnHide geometry obstruction, rather than a two-sided UE physics ray.
// UNREALRED VERIFIED [combat-native-planes-20261104]: Returns float(dot(normal,point)+d) using stored fourth plane scalar, not dot(normal,point-firstCorner). For UE coordinates Pue=100*R*Prf and Nue=R*Nrf, retain Wue=-100*d so UE signed expression dot(Nue,Pue)-Wue equals100*native distance. Do not normalize Nue independently of Wue.
double __thiscall rf_plane_point_signed_distance(float *this, float *a2)
{
  return (float)(rf_vector_dot(a2, this) + *(this + 3));
}

