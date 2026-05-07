# MTeam

A powerful Unreal Engine plugin that extends the built-in `GenericTeamAgentInterface` system, providing a flexible and configurable team management solution for AI and gameplay. MTeam allows you to define custom teams, manage team relationships, and evaluate team affiliations with ease.

## Overview

MTeam simplifies team-based gameplay by providing:

- **Team Definition System**: Create and manage teams using data assets
- **Affiliation Filtering**: Evaluate relationships between actors based on team loyalty (friendly, hostile, neutral)
- **Custom Attitude Solver**: Override default team attitude logic with project-specific rules
- **Blueprint Integration**: Fully exposed to Blueprint for designer-friendly workflows
- **Configuration System**: Manage team attitudes through project settings

## Features

### 🎯 Core Features

- **MTeamComponent**: Actor component that implements `IGenericTeamAgentInterface` for team assignment
- **Team Definition Assets**: Data-driven team configuration with unique team identifiers
- **Affiliation Filters**: Filter actors by their team relationship status (friendly/hostile/neutral)
- **Custom Attitude Overrides**: Define custom attitudes between specific team pairs
- **Blueprint Function Library**: Easy-to-use utilities for team queries and evaluations

### 📊 What You Can Do

- Assign teams to actors (AI characters, players, NPCs)
- Query team relationships between two actors
- Filter for enemies, allies, or neutral actors
- Override default team attitudes with custom rules
- Use team information in AI behavior trees and gameplay systems

## Quick Start

### Step 1: Create Team Definition Assets

1. In the Content Browser, create a new **Data Asset** of type `MTeamDefinitionAsset`
2. Name it (e.g., `DA_PlayerTeam`, `DA_EnemyTeam`, `DA_NeutralTeam`)
3. Assign a unique **Team ID** to each asset

Example structure:
```
Content/
├── Teams/
│   ├── DA_PlayerTeam      (Team ID: 0)
│   ├── DA_EnemyTeam       (Team ID: 1)
│   └── DA_NeutralTeam     (Team ID: 2)
```

### Step 2: Add MTeamComponent to Your Actors

**In Blueprint:**
1. Open your character/pawn blueprint
2. Add `MTeam Component` to the components panel
3. Set the **Team Definition Asset** property to your desired team

**In C++:**
```cpp
#include "Team/MTeamComponent.h"

AMyCharacter::AMyCharacter()
{
    TeamComponent = CreateDefaultSubobject<UMTeamComponent>(TEXT("TeamComponent"));
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();
    TeamComponent->SetTeam(EnemyTeamAsset);
}
```

### Step 3: Query Team Information

Use `UMTeamLibrary` to query and evaluate team relationships.

**In Blueprint:**
1. Use `Get Team ID For Actor` to get an actor's team
2. Use `Evaluate Affiliation Filter For Actors` to check relationships
3. Use `Get Attitude` to determine team attitude

**In C++:**
```cpp
#include "Team/MTeamLibrary.h"

void AEnemyAI::CheckForEnemies()
{
    // Get this actor's team
    FGenericTeamId MyTeamId = UMTeamLibrary::GetTeamIdForActor(this);
    
    // Find enemies nearby
    FMTeamAffiliationFilter EnemyFilter(true, false, false); // enemies only
    
    TArray<AActor*> NearbyEnemies;
    // ... get nearby actors ...
    for (AActor* NearbyActor : NearbyEnemies)
    {
        if (UMTeamLibrary::EvaluateAffiliationFilterForActors(EnemyFilter, this, NearbyActor))
        {
            // Found an enemy!
            EngageTarget(NearbyActor);
        }
    }
}
```

## Configuration

### Setting Up Team Attitudes

1. Create a `MTeamSettings` asset in your project
2. Add entries to **Attitude Overrides** array to define custom relationships between teams
3. For each override, specify:
   - **Team A Definition**: First team
   - **Team B Definition**: Second team  
   - **Attitude**: The relationship (Friendly, Hostile, Neutral)

Example:
```
Attitude Overrides:
  [0] Team A: DA_PlayerTeam, Team B: DA_EnemyTeam → Hostile
  [1] Team A: DA_PlayerTeam, Team B: DA_NeutralTeam → Neutral
  [2] Team A: DA_EnemyTeam, Team B: DA_EnemyTeam → Friendly
```

### Registering the Custom Attitude Solver

In your game module's startup, register the custom attitude solver:

```cpp
// In your Game Module's StartupModule()
#include "Team/MTeamLibrary.h"

void FMyGameModule::StartupModule()
{
    Super::StartupModule();
    UMTeamLibrary::RegisterAttitudeSolver();
}
```

## Usage Examples

### Example 1: AI Selecting Targets

```cpp
void AEnemyCharacter::FindAndAttackNearestEnemy()
{
    FMTeamAffiliationFilter HostileFilter;
    HostileFilter.bHostile = true;
    HostileFilter.bFriendly = false;
    HostileFilter.bNeutral = false;

    AActor* NearestEnemy = nullptr;
    float NearestDistance = FLT_MAX;

    for (AActor* Actor : NearbyActors)
    {
        if (UMTeamLibrary::EvaluateAffiliationFilterForActors(HostileFilter, this, Actor))
        {
            float Distance = FVector::Dist(GetActorLocation(), Actor->GetActorLocation());
            if (Distance < NearestDistance)
            {
                NearestDistance = Distance;
                NearestEnemy = Actor;
            }
        }
    }

    if (NearestEnemy)
    {
        AttackTarget(NearestEnemy);
    }
}
```

### Example 2: Team Sense in Behavior Tree

In Blueprint, create a custom task in a behavior tree:

1. Get all nearby pawns
2. For each pawn, use `Evaluate Affiliation Filter For Actors`
3. Filter by desired relationship (enemy/ally/neutral)
4. Execute logic based on filtered results

## API Reference

### UMTeamComponent

**Methods:**
- `SetTeam(UMTeamDefinitionAsset* InTeamDefinitionAsset)` - Assign team to actor
- `GetAssignedTeam() -> UMTeamDefinitionAsset*` - Get current team

### UMTeamLibrary

**Static Methods:**
- `RegisterAttitudeSolver()` - Register custom attitude solver (call at startup)
- `GetTeamIdForActor(AActor* Actor) -> FGenericTeamId` - Get actor's team ID
- `GetTeamComponentForActor(AActor* Actor) -> UMTeamComponent*` - Get team component
- `GetAttitude(FGenericTeamId A, FGenericTeamId B) -> ETeamAttitude::Type` - Get attitude between teams
- `EvaluateAffiliationFilterForActors(FMTeamAffiliationFilter, AActor*, AActor*) -> bool` - Check relationship between actors
- `EvaluateAffiliationFilterForTeamComponents(FMTeamAffiliationFilter, UMTeamComponent*, UMTeamComponent*) -> bool` - Check relationship between components

### FMTeamAffiliationFilter

**Properties:**
- `bFriendly` - Include friendly units
- `bHostile` - Include hostile units
- `bNeutral` - Include neutral units

**Methods:**
- `GetAsFlags() -> uint8` - Get flags representation
- `Evaluate(FGenericTeamId A, FGenericTeamId B) -> bool` - Evaluate filter against two team IDs

## Requirements

- **MUtility Plugin**: Required core utilities
- **MDeveloperSettings Plugin**: Required for team settings management


