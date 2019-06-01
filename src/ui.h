R"(
<root layout="border">
	<panel param="top" layout="flow" height="20" padding="0" background="false">
		<button name="btnOpen" text="Abrir" width="60" />
		<button name="btnSave" text="Salvar" width="60" />
		<button name="btnSaveAs" text="Salvar Como..." width="120" />
		<button name="btnSaveImg" text="Salvar Imagem" width="120" />
	</panel>
	<splitview param="center" divider="200" orientation="vertical">
		<panel layout="border" background="false" padding="0">
			<panel layout="border" param="top" height="160">
				<label text="Nos" param="top" height="20" />
				<list name="lstNodes" param="center">
					<item>Adicao</item>
					<item>Multiplicacao</item>
					<item>Cor Solida</item>
					<item>Imagem</item>
					<item>Erosao</item>
					<item>Dilatacao</item>
					<item>Mediano</item>
					<item>Convolucao</item>
					<item>Limiar</item>
					<item>Brilho/Contraste</item>
					<item>WebCam</item>
					<item>Espelhamento</item>
					<item>Olho de Peixe</item>
					<item>Mesclar</item>
					<item>Inverter</item>
					<item>Distorcao</item>
				</list>
				<panel layout="flow" height="20" background="false" padding="0" param="bottom">
					<button name="btnAdd" text="+" width="20" />
					<button name="btnDel" text="-" width="20" enabled="false" />
				</panel>
			</panel>
			<panel layout="border" param="center" height="120" background="false" padding="0">
				<panel background="false" param="center" layout="border">
					<label text="Parametros" param="top" />
					<panel name="pnlParams" param="center" layout="stack" background="false" padding="0">

					</panel>
				</panel>
				<panel param="bottom" height="120" layout="stack">
					<label text="Imagem" />
					<spinner name="spnWidth" suffix=" Largura" min="1" max="1024" value="320" step="1" draggable="false" height="20" />
					<spinner name="spnHeight" suffix=" Altura" min="1" max="1024" value="240" step="1" draggable="false" height="20" />
				</panel>
			</panel>
		</panel>

		<splitview divider="400" orientation="horizontal">
			<panel name="pnlView" row="0" layout="grid" gridWidth="1" gridHeight="1" background="false" padding="0"></panel>
			<panel row="1" layout="grid" gridWidth="1" gridHeight="1" background="false" padding="0">
				<imageview name="imgResult" />
			</panel>
		</splitview>
	</splitview>
</root>
)"
