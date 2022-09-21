CREATE FUNCTION fntDistribution (@filmCode int)
	RETURNS TABLE
AS
	RETURN SELECT DistCodeFilm, DistCodeActeur, Acteurs.ActPr�nom, Acteurs.ActNom, DistR�le FROM Distributions INNER JOIN Films ON Distributions.DistCodeFilm = Films.FilmCode INNER JOIN Acteurs ON Distributions.DistCodeActeur = Acteurs.ActCode WHERE Distributions.DistCodeFilm = @filmCode
GO
