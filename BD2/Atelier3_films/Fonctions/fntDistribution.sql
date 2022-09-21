CREATE FUNCTION fntDistribution (@filmCode int)
	RETURNS TABLE
AS
	RETURN SELECT DistCodeFilm, DistCodeActeur, Acteurs.ActPrénom, Acteurs.ActNom, DistRôle FROM Distributions INNER JOIN Films ON Distributions.DistCodeFilm = Films.FilmCode INNER JOIN Acteurs ON Distributions.DistCodeActeur = Acteurs.ActCode WHERE Distributions.DistCodeFilm = @filmCode
GO
