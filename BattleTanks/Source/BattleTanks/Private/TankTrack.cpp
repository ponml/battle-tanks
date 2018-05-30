// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"



void UTankTrack::SetThrottle(float Throttle)
{
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f, at force: %f"), *name, Throttle, TrackMaxDrivingForce);
	//todo clamp actual throttle value so player can't over-drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation(); //location of the track
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent()); //primp comp is a parent class of this obj
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
