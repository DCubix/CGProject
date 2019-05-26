R"(
<root layout="border">
	<panel param="top" layout="flow" height="20" padding="0" background="false">
		<button name="btnOpen" text="Abrir" width="120" />
		<button name="btnSave" text="Salvar" width="130" enabled="false" />
	</panel>
	<panel name="pnlView" param="center" layout="grid" gridWidth="1" gridHeight="1" background="false" padding="0">

	</panel>
	<panel param="right" layout="border" width="220" background="false" padding="0">
		<panel layout="border" param="top" height="220">
			<label text="Nos" param="top" />
			<list param="center">
				<item>Somar</item>
				<item>Multiplicar</item>
				<item>Cor</item>
				<item>Imagem</item>
				<item>Erodir</item>
				<item>Dilatar</item>
				<item>Mediano</item>
				<item>Convoluir</item>
				<item>Limiar</item>
			</list>
			<panel layout="flow" height="20" background="false" padding="0" param="bottom">
				<button name="btnAdd" text="+" width="20" />
			</panel>
		</panel>
		<panel name="pnlParams" layout="stack" param="center">

		</panel>
	</panel>
</root>
)"
