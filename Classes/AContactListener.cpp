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
    if ( ! (sensorA ^ sensorB) )
        return;
    
    int entTypeA=static_cast<Entity*>(fixtureA->GetBody()->GetUserData())->type;
    int entTypeB=static_cast<Entity*>(fixtureB->GetBody()->GetUserData())->type; 
    
    if(entTypeA==ENT_BALL)
    {
        ballEnt=static_cast<Ball*>(fixtureA->GetBody()->GetUserData());
        switch(entTypeB){
            case ENT_BALL:
                break;
            case ENT_HOLE:{
                ballEnt->isAlive=false;
                break;
            }
            case ENT_ENDZONE:{
                EndZone* endEnt=static_cast<EndZone*>(fixtureB->GetBody()->GetUserData());
                endEnt->ballEnter(ballEnt);
                break;
            }
            case ENT_THRUSTER:{
                Thruster* thrustEnt=static_cast<Thruster*>(fixtureB->GetBody()->GetUserData());
                thrustEnt->applyThrust(ballEnt);
                break;
            }
            case ENT_ANTIACCEL:{
                AntiAccel* antiAccEnt= static_cast<AntiAccel*>(fixtureB->GetBody()->GetUserData());
                antiAccEnt->setReverseGravity(ballEnt);
                break;
            }
        }    
    }
    else if(entTypeB==ENT_BALL){
        
        ballEnt=static_cast<Ball*>(fixtureB->GetBody()->GetUserData());
        switch(entTypeA){
            case ENT_BALL:
                break;
            case ENT_HOLE:{
                ballEnt->isAlive=false;
                break;
            }
            case ENT_ENDZONE:{
                EndZone* endEnt=static_cast<EndZone*>(fixtureA->GetBody()->GetUserData());
                endEnt->ballEnter(ballEnt);
                break;
            }
            case ENT_THRUSTER:{
                Thruster* thrustEnt=static_cast<Thruster*>(fixtureA->GetBody()->GetUserData());
                thrustEnt->applyThrust(ballEnt);
                break;
            }
            case ENT_ANTIACCEL:{
                AntiAccel* antiAccEnt= static_cast<AntiAccel*>(fixtureA->GetBody()->GetUserData());
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
    if ( ! (sensorA ^ sensorB) )
        return;
    
    int entTypeA=static_cast<Entity*>(fixtureA->GetBody()->GetUserData())->type;
    int entTypeB=static_cast<Entity*>(fixtureB->GetBody()->GetUserData())->type; 
    
    if(entTypeA==ENT_BALL)
    {
        ballEnt=static_cast<Ball*>(fixtureA->GetBody()->GetUserData());
        switch(entTypeB){
            case ENT_BALL:
                break;
            case ENT_HOLE:
                break;
            case ENT_ENDZONE:{
                EndZone* endEnt=static_cast<EndZone*>(fixtureB->GetBody()->GetUserData());
                endEnt->ballExit(ballEnt);
                break;
            }
            case ENT_THRUSTER:
                break;
            case ENT_ANTIACCEL:{
                AntiAccel* antiAccEnt= static_cast<AntiAccel*>(fixtureB->GetBody()->GetUserData());
                antiAccEnt->setNormalGravity(ballEnt);
                break;
            }
        }    
    }
    else if(entTypeB==ENT_BALL){
        
        ballEnt=static_cast<Ball*>(fixtureB->GetBody()->GetUserData());
        switch(entTypeA){
            case ENT_BALL:
                break;
            case ENT_HOLE:
                break;
            case ENT_ENDZONE:{
                EndZone* endEnt=static_cast<EndZone*>(fixtureA->GetBody()->GetUserData());
                endEnt->ballExit(ballEnt);
                break;
            }
            case ENT_THRUSTER:
                break;
            case ENT_ANTIACCEL:{
                AntiAccel* antiAccEnt= static_cast<AntiAccel*>(fixtureA->GetBody()->GetUserData());
                antiAccEnt->setNormalGravity(ballEnt);
                break;
            }
        }       
        
    }
   
}
