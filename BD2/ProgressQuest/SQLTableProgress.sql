CREATE DATABASE ProgressQuest
ON PRIMARY
(
    NAME = 'ProgressQuest',
    FILENAME = 'C:\Users\Public\ProgressQuest.mdf',
    SIZE = 30MB,
    MAXSIZE = 50MB,
    FILEGROWTH = 5MB
)
LOG ON
(
    NAME = 'ProgressQuest_log',
    FILENAME = N'C:\Users\Public\ProgressQuest_log.ldf',
    SIZE = 10MB,
    MAXSIZE = 12MB,
    FILEGROWTH = 5MB

)
GO

USE ProgressQuest
GO

CREATE TABLE Personnage (
    PersoCode int NOT NULL identity,
    PersoNom nvarchar(30) NOT NULL,
    PersoRaceCode int NOT NULL, 
    PersoClasseCode int NOT NULL,
    PersoXp int NOT NULL,
    PersoLevel int NOT NULL,
    PersoHp int NOT NULL,
    PersoMaxHp int NOT NULL,
    PersoForce int NOT NULL,
    PersoDefense int NOT NULL,
    PersoDext int NOT NULL,
    PersoOr int NOT NULL,
    CONSTRAINT PK_PersoCode PRIMARY KEY (PersoCode)
)
GO

CREATE TABLE Race(
    RaceCode int NOT NULL identity,
    RaceNom nvarchar(30) NOT NULL,
    CONSTRAINT PK_RaceCode PRIMARY KEY (RaceCode)
)
GO

CREATE TABLE RaceClasse(
    RaceClassCode int NOT NULL identity,
    RaceClassRaceCode int NOT NULL,
    RaceClassClasseCode int NOT NULL,
    CONSTRAINT PK_RaceClassCode PRIMARY KEY (RaceClassCode)
)
GO

CREATE TABLE Classe (
    ClasseCode int NOT NULL identity,
    ClasseNom nvarchar(30) NOT NULL,
    ClasseForceQte int NOT NULL,
    ClasseDefQte int NOT NULL,
    ClasseDextQte int NOT NULL,
    ClasseHpQte int NOT NULL,
    ClasseOrQte int NOT NULL,
    CONSTRAINT PK_ClasseCode PRIMARY KEY (ClasseCode)
)
GO

CREATE TABLE Inventaire (
    InvCode int NOT NULL IDENTITY,
    InvPersoCode int NOT NULL,
    InvItemCode int NOT NULL,
    InvItemQte int NOT NULL,
    CONSTRAINT PK_InvCode PRIMARY KEY (InvCode)
)
GO

CREATE TABLE EquipementInventaire (
    EquipInvCode int NOT NULL IDENTITY,
    EquipInvPersoCode int NOT NULL,
    EquipIntEquipementCode int NOT NULL,
    CONSTRAINT PK_EquipInvCode PRIMARY KEY (EquipInvCode)
)
GO

CREATE TABLE Equipement (
    EquipCode int NOT NULL IDENTITY,
    EquipNom nvarchar(30) NOT NULL,
    EquipValeur int NOT NULL,
    EquipEmplacementCode int NOT NULL,
    CONSTRAINT PK_EquipCode PRIMARY KEY (EquipCode)
)
GO

CREATE TABLE Emplacement (
    EmplacementCode int NOT NULL IDENTITY,
    EmplacementNom nvarchar(30) NOT NULL,
    CONSTRAINT PK_EmplacementCode PRIMARY KEY (EmplacementCode)
)
GO

--Table contenant les ennemis ainsi que leurs statistiques
CREATE TABLE Ennemi(
    EnnemiCode int NOT NULL,
    EnnemiNom nvarchar(30) DEFAULT(''),
    EnnemieLevel int DEFAULT(1),
    EnnemiMaxHp int DEFAULT(1),
    EnnemiHp int DEFAULT(1),
    EnnemiForce int DEFAULT(1),
    EnnemiDefense int DEFAULT(1),
    estBoss binary(1) DEFAULT(0),
    
    CONSTRAINT PK_ennemi_id PRIMARY KEY (EnnemiCode)
)
GO

CREATE TABLE Item(
    ItemCode int NOT NULL IDENTITY(1,1),
    ItemNom nvarchar(30) DEFAULT(''),
    ItemValeur int DEFAULT(0),
    
    CONSTRAINT PK_item_id PRIMARY KEY (ItemCode)
)
GO


CREATE TABLE ButinEnnemi(
    ButinEnnCode int NOT NULL IDENTITY(1,1),
    ButinEnnEnnemiCode int NOT NULL,
    ButinEnnItemCode int NOT NULL,
    ButinEnnItemQte int DEFAULT(1),
    
    CONSTRAINT PK_butinEnnemi_id PRIMARY KEY (ButinEnnCode)
)
GO

CREATE TABLE DonjEnnemi(
    DonjEnnCode int NOT NULL IDENTITY(1,1),
    DonjEnnEnnemiCode int NOT NULL,
    DonjEnnDonjonCode int NOT NULL,
    
    CONSTRAINT PK_donjEnnemi_id PRIMARY KEY (DonjEnnCode)
)
GO

CREATE TABLE ButinDonjon(
    ButinDonjCode int NOT NULL IDENTITY(1,1),
    ButinDonjDonjonCode int NOT NULL,
    ButinDonjItemCode int NOT NULL,
    ButinDonjOrQte int NOT NULL,
    ButinDonjXpQte int NOT NULL,
    ButinDonjItemQte int NOT NULL,
    
    CONSTRAINT PK_butinDonjon_id PRIMARY KEY (ButinDonjCode)
)
GO

CREATE TABLE Donjon(
    DonjCode int NOT NULL IDENTITY(1,1),
    DonjNom nvarchar(30) DEFAULT(''),
    DonjLevel int DEFAULT(1),
    DonjNbEnnemi int DEFAULT(1),
    DonjEnnemiCode int NOT NULL,
    
    CONSTRAINT PK_butinDonjon_id PRIMARY KEY (DonjCode)
)
GO

CREATE TABLE ButinQuete(
    ButinQueCode int NOT NULL IDENTITY(1,1),
    ButinQueQueteCode int NOT NULL,
    ButinQueItemCode int NOT NULL,
    
    CONSTRAINT PK_butinDonjon_id PRIMARY KEY (ButinQueCode)
)
GO

CREATE TABLE Quete(
    QueteCode int NOT NULL,
    QueteNom nvarchar(30) DEFAULT(''),
    QueteDescription nvarchar(64) DEFAULT(''),
    QueteLevel int DEFAULT(1),
    QueteItemCode int NOT NULL,
    QueteItemQte int DEFAULT(1),
    QueteOrQte int DEFAULT(1),
    QueteXpQte int DEFAULT(1),
    QueteDonjonCode int NOT NULL,
    QueteEquipementCode int NOT NULL,

    
    CONSTRAINT PK_quete_id PRIMARY KEY (QueteCode)
)
GO

ALTER TABLE Personnage ADD 
CONSTRAINT FK_PersoRaceCode FOREIGN KEY (PersoRaceCode) REFERENCES Race (RaceCode),
CONSTRAINT FK_PersoClasseCode FOREIGN KEY (PersoClasseCode) REFERENCES Classe (ClasseCode);
GO

ALTER TABLE RaceClasse ADD
CONSTRAINT FK_RaceClassRaceCode FOREIGN KEY (RaceClassRaceCode) REFERENCES Race (RaceCode),
CONSTRAINT FK_RaceClassClasseCode FOREIGN KEY (RaceClassClasseCode) REFERENCES Classe (ClasseCode);
GO

ALTER TABLE Inventaire ADD
CONSTRAINT FK_InvPersoCode FOREIGN KEY (InvPersoCode) REFERENCES Personnage (PersoCode),
CONSTRAINT FK_InvItemCode FOREIGN KEY (InvItemCode) REFERENCES Item (ItemCode);
GO

ALTER TABLE EquipementInventaire ADD
CONSTRAINT FK_EquipInvPersoCode FOREIGN KEY (EquipInvPersoCode) REFERENCES Personnage (PersoCode),
CONSTRAINT FK_EquipIntEquipementCode FOREIGN KEY (EquipIntEquipementCode) REFERENCES Equipement (EquipCode);
GO

ALTER TABLE Equipement ADD
CONSTRAINT FK_EquipEmplacementCode FOREIGN KEY (EquipEmplacementCode) REFERENCES Emplacement (EmplacementCode);
GO

ALTER TABLE ButinEnnemi ADD
CONSTRAINT FK_ButinEnnEnnemiCode FOREIGN KEY (ButinEnnEnnemiCode) REFERENCES Ennemi (EnnemiCode),
CONSTRAINT FK_ButinEnnItemCode FOREIGN KEY (ButinEnnItemCode) REFERENCES Item (ItemCode);
GO

ALTER TABLE DonjEnnemi ADD
CONSTRAINT FK_DonjEnnEnnemiCode FOREIGN KEY (DonjEnnEnnemiCode) REFERENCES Ennemi (EnnemiCode),
CONSTRAINT FK_DonjEnnDonjonCode FOREIGN KEY (DonjEnnDonjonCode) REFERENCES Donjon (DonjCode);
GO

ALTER TABLE ButinDonjon ADD
CONSTRAINT FK_ButinDonjDonjonCode FOREIGN KEY (ButinDonjDonjonCode) REFERENCES Donjon (DonjCode),
CONSTRAINT FK_ButinDonjItemCode FOREIGN KEY (ButinDonjItemCode) REFERENCES Item (ItemCode);
GO

ALTER TABLE Donjon ADD
CONSTRAINT FK_DonjEnnemiCode FOREIGN KEY (DonjEnnemiCode) REFERENCES Ennemi (EnnemiCode);
GO

ALTER TABLE ButinQuete ADD
CONSTRAINT FK_ButinQueQueteCode FOREIGN KEY (ButinQueQueteCode) REFERENCES Quete (QueteCode),
CONSTRAINT FK_ButinQueItemCode FOREIGN KEY (ButinQueItemCode) REFERENCES Item (ItemCode);
GO

ALTER TABLE Quete ADD
CONSTRAINT FK_QueteItemCode FOREIGN KEY (QueteItemCode) REFERENCES Item (ItemCode),
CONSTRAINT FK_QueteDonjonCode FOREIGN KEY (QueteDonjonCode) REFERENCES Donjon (DonjCode),
CONSTRAINT QueteEquipementCode FOREIGN KEY (QueteEquipementCode) REFERENCES Equipement (EquipCode);
GO


