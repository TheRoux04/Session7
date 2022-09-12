

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
    
    CONSTRAINT PK_butinDonjon_id PRIMARY KEY (ButinDonjCode)
)
GO

CREATE TABLE ButinQuete(
    ButinQueCode int NOT NULL IDENTITY(1,1),
    ButinQueQueteCode int NOT NULL,
    ButinQueItemCode int NOT NULL,
    
    CONSTRAINT PK_butinDonjon_id PRIMARY KEY (ButinDonjCode)
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