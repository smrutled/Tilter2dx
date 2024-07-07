//
//  AContactListener.cpp
//  Tilter2d
//
//  Created by Sean on 4/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "AContactListener.h"
#include "Entity.h"
#include "Ball.h"
#include "EndZone.h"
#include "Hole.h"
#include "Thruster.h"
#include "AntiAccel.h"

void AContactListener::BeginContact(b2Contact* contact) {
	Ball* ballEnt;
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//make sure that ball collided with a sensor
	bool sensorA = fixtureA->IsSensor();
	bool sensorB = fixtureB->IsSensor();
	if (!(sensorA ^ sensorB))
		return;

	int entTypeA = reinterpret_cast<Entity*>(fixtureA->GetBody()->GetUserData().pointer)->type;
    int entTypeB = reinterpret_cast<Entity*>(fixtureB->GetBody()->GetUserData().pointer)->type;

	if (entTypeA == ENT_BALL)
	{
		ballEnt = reinterpret_cast<Ball*>(fixtureA->GetBody()->GetUserData().pointer);
		switch (entTypeB){
		case ENT_BALL:
			break;
		case ENT_HOLE:{
			ballEnt->isAlive = false;
			break;
			}
		case ENT_ENDZONE:{
			EndZone* endEnt = reinterpret_cast<EndZone*>(fixtureB->GetBody()->GetUserData().pointer);
			endEnt->ballEnter(ballEnt);
			break;
			}
		case ENT_THRUSTER:{
			Thruster* thrustEnt = reinterpret_cast<Thruster*>(fixtureB->GetBody()->GetUserData().pointer);
			thrustEnt->applyThrust(ballEnt);
			break;
			}
		case ENT_ANTIACCEL:{
			AntiAccel* antiAccEnt = reinterpret_cast<AntiAccel*>(fixtureB->GetBody()->GetUserData().pointer);
			antiAccEnt->setReverseGravity(ballEnt);
			break;
			}
		}
	}
	else if (entTypeB == ENT_BALL){

		ballEnt = reinterpret_cast<Ball*>(fixtureB->GetBody()->GetUserData().pointer);
		switch (entTypeA){
		case ENT_BALL:
			break;
		case ENT_HOLE:{
			ballEnt->isAlive = false;
			break;
			}
		case ENT_ENDZONE:{
			EndZone* endEnt = reinterpret_cast<EndZone*>(fixtureA->GetBody()->GetUserData().pointer);
			endEnt->ballEnter(ballEnt);
			break;
			}
		case ENT_THRUSTER:{
			Thruster* thrustEnt = reinterpret_cast<Thruster*>(fixtureA->GetBody()->GetUserData().pointer);
			thrustEnt->applyThrust(ballEnt);
			break;
			}
		case ENT_ANTIACCEL:{
			AntiAccel* antiAccEnt = reinterpret_cast<AntiAccel*>(fixtureA->GetBody()->GetUserData().pointer);
			antiAccEnt->setReverseGravity(ballEnt);
			break;
			}
		}

	}


}

void AContactListener::EndContact(b2Contact* contact) {
	Ball* ballEnt;
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//make sure that ball collided with a sensor
	bool sensorA = fixtureA->IsSensor();
	bool sensorB = fixtureB->IsSensor();
	if (!(sensorA ^ sensorB))
		return;

	int entTypeA = reinterpret_cast<Entity*>(fixtureA->GetBody()->GetUserData().pointer)->type;
	int entTypeB = reinterpret_cast<Entity*>(fixtureB->GetBody()->GetUserData().pointer)->type;

	if (entTypeA == ENT_BALL)
	{
		ballEnt = reinterpret_cast<Ball*>(fixtureA->GetBody()->GetUserData().pointer);
		switch (entTypeB){
		case ENT_BALL:
			break;
		case ENT_HOLE:
			break;
		case ENT_ENDZONE:{
			EndZone* endEnt = reinterpret_cast<EndZone*>(fixtureB->GetBody()->GetUserData().pointer);
			endEnt->ballExit(ballEnt);
			break;
			}
		case ENT_THRUSTER:
			break;
		case ENT_ANTIACCEL:{
			AntiAccel* antiAccEnt = reinterpret_cast<AntiAccel*>(fixtureB->GetBody()->GetUserData().pointer);
			antiAccEnt->setNormalGravity(ballEnt);
			break;
			}
		}
	}
	else if (entTypeB == ENT_BALL){

		ballEnt = reinterpret_cast<Ball*>(fixtureB->GetBody()->GetUserData().pointer);
		switch (entTypeA){
		case ENT_BALL:
			break;
		case ENT_HOLE:
			break;
		case ENT_ENDZONE:{
			EndZone* endEnt = reinterpret_cast<EndZone*>(fixtureA->GetBody()->GetUserData().pointer);
			endEnt->ballExit(ballEnt);
			break;
			}
		case ENT_THRUSTER:
			break;
		case ENT_ANTIACCEL:{
			AntiAccel* antiAccEnt = reinterpret_cast<AntiAccel*>(fixtureA->GetBody()->GetUserData().pointer);
			antiAccEnt->setNormalGravity(ballEnt);
			break;
			}
		}

	}

}
