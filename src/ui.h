R"(
<root layout="border">
	<panel param="top" layout="flow" height="20" padding="0" background="false">
		<button name="btnOpen" text="Abrir" width="60" />
		<button name="btnSave" text="Salvar" width="60" enabled="false" />
	</panel>
	<panel param="center" layout="grid" gridWidth="1" gridHeight="2" padding="0">
		<panel name="pnlView" row="0" layout="grid" gridWidth="1" gridHeight="1" background="false" padding="0"></panel>
		<panel row="1" layout="grid" gridWidth="1" gridHeight="1" background="false" padding="0">
			<imageview name="imgResult" />
		</panel>
	</panel>
	<panel param="right" layout="border" width="220" background="false" padding="0">
		<panel layout="border" param="top" height="160">
			<label text="Nos" param="top" />
			<list name="lstNodes" param="center">
				<item>Somar</item>
				<item>Multiplicar</item>
				<item>Cor</item>
				<item>Imagem</item>
				<item>Erodir</item>
				<item>Dilatar</item>
				<item>Mediano</item>
				<item>Convoluir</item>
				<item>Limiar</item>
				<item>Brilho/Contraste</item>
				<item>WebCam</item>
				<item>Espelhar</item>
				<item>Olho de Peixe</item>
				<item>Mesclar</item>
				<item>Inverter</item>
				<item>Distorcer</item>
			</list>
			<panel layout="flow" height="20" background="false" padding="0" param="bottom">
				<button name="btnAdd" text="+" width="20" />
				<button name="btnDel" text="-" width="20" enabled="false" />
			</panel>
		</panel>
		<panel layout="border" param="center" height="120" background="false" padding="0">
			<panel param="bottom" height="120" layout="stack">
				<label text="Imagem" />
				<spinner name="spnWidth" suffix=" Largura" min="1" max="1024" value="320" step="1" draggable="false" height="20" />
				<spinner name="spnHeight" suffix=" Altura" min="1" max="1024" value="240" step="1" draggable="false" height="20" />
				<button name="btnProc" text="Processar" height="20" />
				<check name="chkHalf" text="Mostrar Original" height="20" />
			</panel>
			<panel name="pnlParams" param="center" layout="stack" background="false">

			</panel>
		</panel>
	</panel>
</root>
)"
