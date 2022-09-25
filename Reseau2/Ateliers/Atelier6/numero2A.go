package main

import (
	"fmt"
	"image"
	"image/gif"
	"image/jpeg"
	"image/png"
	"io"
	"net/http"
	"net/url"
	"os"
)

func main() {
	for i := 0; i < 10; i++ {
		go estPremier()
	}
	var input string
	fmt.Scanln(&input)
}

func thumbnailHandler() http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {

		filename, err := url.QueryUnescape(r.URL.String())
		checkErr(err)

		fmt.Println("handling request for", filename)

		file, err := os.Open(filename)
		checkErr(err)
		defer file.Close()

		img, filetype, err := image.Decode(file)
		checkErr(err)

		var newImage image.Image

		if thumbnailSize < img.Bounds().Dx() || thumbnailSize < img.Bounds().Dy() {
			if img.Bounds().Dx() > img.Bounds().Dy() {
				newImage = resize.Resize(uint(thumbnailSize), 0, img, resize.Lanczos3)
			} else {
				newImage = resize.Resize(0, uint(thumbnailSize), img, resize.Lanczos3)
			}
		} else {
			newImage = img
		}

		switch filetype {
		case "png":
			err = png.Encode(w, newImage)
		case "gif":
			err = gif.Encode(w, newImage, nil)
		case "jpeg", "jpg":
			err = jpeg.Encode(w, newImage, nil)
		case "bmp":
			err = bmp.Encode(w, newImage)
		case "tiff":
			err = tiff.Encode(w, newImage, nil)
		default:
			// not sure how you got here but what are we going to do with you?
			fmt.Println("Unknown image type: ", filetype)
			io.Copy(w, file)
		}
		checkErr(err)
		fmt.Println("done handling request")

	})
}
