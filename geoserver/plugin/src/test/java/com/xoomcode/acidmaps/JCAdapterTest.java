/**
 * 
 */
package com.xoomcode.acidmaps;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import org.apache.commons.lang.ArrayUtils;

import junit.framework.TestCase;

import com.xoomcode.acidmaps.adapter.JCAdapter;
import com.xoomcode.acidmaps.constants.Constants;
import com.xoomcode.acidmaps.core.Bounds;
import com.xoomcode.acidmaps.core.Configuration;
import com.xoomcode.acidmaps.interpolate.InterpolationStrategy;
import com.xoomcode.acidmaps.renderer.RendererType;
import com.xoomcode.acidmaps.simplify.SimplifyMethod;

/**
 * @date 09/11/2010
 * @author cfarina
 * 
 */
public class JCAdapterTest extends TestCase {

	private Configuration configuration = new Configuration();

	/**
	 * @see junit.framework.TestCase#setUp()
	 */
	@Override
	protected void setUp() throws Exception {
		configuration = new Configuration();
	    configuration.dataset = createDataset();
	    //configuration.datasetSize = 10;
	    configuration.simplifyMethod = SimplifyMethod.COPY;
	    configuration.simplifySize = 6;
	    configuration.bounds = new Bounds(-180, -90, 180, 90);
	    configuration.width = 1024;
	    configuration.height = 512;
	    configuration.intervals = createIntervals();
	    configuration.intervalsColors = createIntervalsColors();
	    //configuration.intervalsSize = 5;
	    configuration.intervalsType = RendererType.SPARSE;
		super.setUp();
	}
	
	private byte[] createIntervalsColors() {
	    byte[] colors = new byte[5 * Constants.RGBA];
	    colors[0] = 0x00; colors[1] = 0x00; colors[2] = 0x00; colors[3] = 0x00;
	    colors[4] = (byte)0xFF; colors[5] = 0x30; colors[6] = 0x30; colors[7] = (byte)0x90;
	    colors[8] = (byte)0xFF; colors[9] = (byte)0x90; colors[10] = 0x10; colors[11] = (byte)0xB0;
	    colors[12] = 0x00; colors[13] = (byte)0xFF; colors[14] = 0x30; colors[15] = (byte)0xFF;
	    colors[16] = 0x00; colors[17] = 0x30; colors[18] = (byte)0xFF; colors[19] = (byte)0xFF;
	    return colors; 
	}

	private int[] createIntervals() {
		int[] intervals = new int[5];
		intervals[0] = 10;
		intervals[1] = 22;
		intervals[2] = 45;
		intervals[3] = 70;
		intervals[4] = 110;
		return intervals;
	}

	private float[] createDataset() {
		float[] dataset = new float[10 * Constants.VPP];
		/*for (int i = 0; i < 10; i++) {
			dataset[i * Constants.VPP] = (float) Math.random() % 360 - 180;
			dataset[i * Constants.VPP + 1] = (float) Math.random() % 180 - 90;
			dataset[i * Constants.VPP + 2] = (float) Math.random() % 150;
		}*/
		
		dataset[0] = 163; dataset[1] = 16;  dataset[2] = 27;
		dataset[3] = -65; dataset[4] = 23;  dataset[5] = 85;
		dataset[6] = 46;  dataset[7] = -78; dataset[8] = 99;
		dataset[9] = 1;   dataset[10] = 32;	dataset[11] = 127; 
		dataset[12] = -130; dataset[13] = -11; dataset[14] = 113;
		dataset[15] = -14;  dataset[16] = -30; dataset[17] = 126;
		dataset[18] = -128; dataset[19] = 46; dataset[20] = 11;
		dataset[21] = -172; dataset[22] = -3; dataset[23] = 129;
		dataset[24] = -118; dataset[25] = 80; dataset[26] = 62;
		dataset[27] = 103; dataset[28] = 37; dataset[29] = 85;
		
		return dataset;
	}

	/**
	 * 
	 */
	public void testAcidMap() {
		JCAdapter jCAdapter = new JCAdapter();

		configuration.interpolationStrategy = InterpolationStrategy.LINEAR;
		configuration.interpolationParameter = 32;
		byte[] outputBuffer = jCAdapter.interpolate(configuration);

		try {
			FileOutputStream fos = new FileOutputStream("image.png");
			fos.write(outputBuffer);
			fos.close();
		} catch (FileNotFoundException ex) {
			System.out.println("FileNotFoundException : " + ex);
		} catch (IOException ioe) {
			System.out.println("IOException : " + ioe);
		}
	}

}
