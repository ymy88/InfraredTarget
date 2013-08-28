CREATE TABLE EnemyMissiles (
msslId integer primary key,
name text not null unique,
speed real not null,
baitcnt int not null,
modelfile text not null);

CREATE TABLE Locations (
locId integer primary key,
name text not null unique,
lon real not null,
lat real not null,
dscpt text);

CREATE TABLE OurMissiles (
msslId integer primary key,
name text not null unique,
speed real not null,
anglerate real not null,
modelfile text not null);

CREATE TABLE Presets (
presetId integer primary key,
enemyMsslId integer references EnemyMissiles(msslId) on update cascade on delete cascade,
enemyLocId integer references Locations(locId) on update cascade on delete cascade,
enemyAlt real not null,
enemyThetaEarth real null,
enemyThetaNorth real null,
ourMsslId integer references OurMissiles(msslId) on update cascade on delete cascade,
ourLocId integer references Locations(locId) on update cascade on delete cascade,
ourAlt real not null,
ourThetaEarth real not null,
ourThetaNorth real not null,
ourDelayTime real not null default 0,
cameraAngle real not null,
resolution int not null default 512,
blindRate real not null,
updateRate int not null,
saveToFile int not null default 0,
initDist real not null default 200
);