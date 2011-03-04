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
import com.xoomcode.acidmaps.core.Point;
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
	    configuration.simplifyMethod = SimplifyMethod.GRID;
	    configuration.simplifySize = 6;
	    configuration.interpolationStrategy = InterpolationStrategy.INVERSE_DISTANCE_WEIGHTING;
	    configuration.bounds = new Bounds(-180, -90, 180, 90);
	    configuration.width = 1024;
	    configuration.height = 512;
	    configuration.intervals = createIntervals();
	    configuration.intervalsColors = createIntervalsColors();
	    configuration.rendererType = RendererType.SPARSE;
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

	private float[] createIntervals() {
		float[] intervals = new float[5];
		intervals[0] = 10;
		intervals[1] = 22;
		intervals[2] = 45;
		intervals[3] = 70;
		intervals[4] = 110;
		return intervals;
	}

	private Point[] createDataset() {
		Point[] dataset = new Point[10];
		
		dataset[0] = new Point(163, 16, 27);
		dataset[1] = new Point(-65, 23, 85);
		dataset[2] = new Point(46, -78, 99);
		dataset[3] = new Point(1, 32, 127); 
		dataset[4] = new Point(-130, -11, 113);
		dataset[5] = new Point(-14, -30, 126);
		dataset[6] = new Point(-128, 46, 11);
		dataset[7] = new Point(-172, -3, 129);
		dataset[8] = new Point(-118, 80, 62);
		dataset[9] = new Point(103, 37, 85);
		
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
		assertNotNull(outputBuffer);
		/*try {
			FileOutputStream fos = new FileOutputStream("image.png");
			fos.write(outputBuffer);
			fos.close();
		} catch (FileNotFoundException ex) {
			System.out.println("FileNotFoundException : " + ex);
		} catch (IOException ioe) {
			System.out.println("IOException : " + ioe);
		}*/
	}

}
