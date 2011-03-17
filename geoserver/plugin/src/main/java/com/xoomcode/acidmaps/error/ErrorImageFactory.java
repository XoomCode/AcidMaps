package com.xoomcode.acidmaps.error;

import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

public class ErrorImageFactory {

	public BufferedImage getErrorImage(int width, int height, String message) {
		
		BufferedImage image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
		
		// Create a graphics contents on the buffered image
		Graphics2D g2d = image.createGraphics();

		// Draw graphics
		g2d.setColor(java.awt.Color.white);
		g2d.fillRect(0, 0, width, height);
//		g2d.setColor(java.awt.Color.gray);
//		g2d.drawRect(0, 0, width, height);
		g2d.setColor(java.awt.Color.black);
		g2d.setFont(new Font("SansSerif", Font.BOLD, 12 ));
		
		FontMetrics fm = g2d.getFontMetrics();
	    int textWidth = fm.stringWidth(message);
	    int parts = (int)Math.ceil(textWidth / (width * 1.0));
	    int partLength = message.length() / parts;
	    int lineHeight = 20;
	    
	    int from = 0;
	    int to = 0;
	    int cursor = 0;
	    int i = 0;
	    do {
			from = cursor;
	    	to = from + partLength;
			if(to >= message.length()){
				to = message.length();
			}
			String part = message.substring(from, to);
			int lastSpaceIndex = part.lastIndexOf(" ");
			if(lastSpaceIndex == 0){
				lastSpaceIndex = part.length();
			}
			String fixedPart;
			if(lastSpaceIndex != -1){
				fixedPart = part.substring(0, lastSpaceIndex);
			} else {
				fixedPart = part;
				lastSpaceIndex = part.length();
			}
			g2d.drawString(fixedPart.trim(), 5, 10 + lineHeight* (i + 1));
			cursor += lastSpaceIndex;
			i++;
		}while(cursor < message.length() || (i * lineHeight > height));
	    
		// Graphics context no longer needed so dispose it
		g2d.dispose();
		return image;
	}
	
}
