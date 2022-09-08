CREATE DATABASE Atelier1
ON PRIMARY
(
NAME = 'Atelier1',
FILENAME = N'C:\Users\Public\Atelier1.mdf',
SIZE = 5MB,
MAXSIZE = 10MB,
FILEGROWTH = 1MB
)
LOG ON
(
NAME = 'Atelier1_log',
FILENAME = N'C:\Users\Public\Atelier1_log.ldf',
SIZE = 1MB,
MAXSIZE = 2MB,
FILEGROWTH = 1MB
)

GO

USE Atelier1
GO

CREATE TABLE Produits (
    produit_code bigint NOT NULL identity(1, 1),
    produit_nom nvarchar(64) NOT NULL,
    produit_prix float NOT NULL,
    CONSTRAINT PK_produit_code PRIMARY KEY (produit_code),
)

GO

CREATE TABLE Vendeurs (
    vendeur_code bigint NOT NULL identity(1, 1),
    vendeur_nom nvarchar(64) NOT NULL,
    vendeur_jour int NOT NULL CHECK (vendeur_jour < 32),
    vendeur_mois int NOT NULL CHECK (vendeur_mois < 13),
    vendeur_annee int NOT NULL,
    CONSTRAINT PK_vendeur_code PRIMARY KEY (vendeur_code),
)

GO

CREATE TABLE Ventes (
    vente_code bigint NOT NULL identity(1, 1),
    vente_produit_code bigint NOT NULL,
    vente_vendeur_code bigint NOT NULL,
    CONSTRAINT PK_vente_code PRIMARY KEY (vente_code),
    CONSTRAINT FK_produit_code FOREIGN KEY (vente_produit_code) REFERENCES Produits (produit_code),
    CONSTRAINT FK_vendeur_code FOREIGN KEY (vente_vendeur_code) REFERENCES Vendeurs (vendeur_code)
)
GO