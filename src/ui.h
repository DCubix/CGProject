R"(
<root layout="border">
	<panel param="top" layout="flow" height="20" padding="0" background="false">
		<button name="btnOpen" text="Open" width="60" />
		<button name="btnSave" text="Save" width="60" />
		<button name="btnSaveAs" text="Save As..." width="120" />
		<button name="btnSaveImg" text="Save Image" width="120" />
	</panel>
	<panel param="bottom" layout="flow" height="16" padding="2" background="false">
		<label text="Diego Lopes - diego95lopes@gmail.com - v1.1.0" width="480" height="14" />
	</panel>
	<splitview param="center" divider="200" orientation="vertical">
		<panel layout="border" background="false" padding="0">
			<panel layout="border" param="top" height="160">
				<label text="Nodes" param="top" height="20" />
				<list name="lstNodes" param="center">
					<item>Add</item>
					<item>Multiply</item>
					<item>Solid Color</item>
					<item>Image</item>
					<item>Erode</item>
					<item>Dilate</item>
					<item>Median</item>
					<item>Convolute</item>
					<item>Threshold</item>
					<item>Brightness/Contrast</item>
					<item>WebCam</item>
					<item>Mirror</item>
					<item>Fish Eye</item>
					<item>Mix</item>
					<item>Invert</item>
					<item>Distort</item>
					<!--<item>Script</item>-->
					<item>Normal Map</item>
					<item>Grayscale</item>
				</list>
				<panel layout="flow" height="20" background="false" padding="0" param="bottom">
					<button name="btnAdd" text="+" width="20" />
					<button name="btnDel" text="-" width="20" enabled="false" />
				</panel>
			</panel>
			<panel layout="border" param="center" height="120" background="false" padding="0">
				<panel background="false" param="center" layout="border">
					<label text="Parameters" param="top" />
					<panel name="pnlParams" param="center" layout="stack" background="false" padding="0">

					</panel>
				</panel>
				<panel param="bottom" height="120" layout="stack">
					<label text="Image" />
					<spinner name="spnWidth" suffix=" Width" min="1" max="1024" value="320" step="1" draggable="false" height="20" />
					<spinner name="spnHeight" suffix=" Height" min="1" max="1024" value="240" step="1" draggable="false" height="20" />
				</panel>
			</panel>
		</panel>

		<splitview divider="300" orientation="horizontal">
			<panel name="pnlView" row="0" layout="grid" gridWidth="1" gridHeight="1" background="false" padding="0"></panel>
			<panel row="1" layout="grid" gridWidth="1" gridHeight="1" background="false" padding="0">
				<imageview name="imgResult" />
			</panel>
		</splitview>
	</splitview>
</root>
)"
