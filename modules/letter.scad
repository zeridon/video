/**
 * Simple module to print letters
 */

module letter(letter, size = 4, height = 1, font) {
	linear_extrude(height = height) {
		text(letter, size = size, font = font, halign = "center", valign = "center", $fn = 16);
	}
}