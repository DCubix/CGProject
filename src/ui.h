R"(
<root layout="border">
	<panel param="top" layout="flow" height="20" padding="0" background="false">
		<button name="btnOpen" text="Abrir Imagem" width="120" />
		<button name="btnSave" text="Salvar Imagem" width="130" enabled="false" />
	</panel>
	<panel param="center" layout="grid" gridWidth="2" gridHeight="1">
		<panel col="0" layout="border" padding="2" background="false">
			<label text="Original" param="top" />
			<imageview name="A" param="center" />
		</panel>
		<panel col="1" layout="border" padding="2" background="false">
			<label text="Processada" param="top" />
			<imageview name="B" param="center" />
		</panel>
	</panel>
	<panel param="bottom" layout="border" height="150" background="false" padding="0">
		<panel param="left" width="220" layout="border" gridWidth="2" gridHeight="4">
			<label param="top" text="Filtros" />
			<panel param="center" width="220" layout="grid" gridWidth="2" gridHeight="4">
				<button name="btnDilation" text="Dilatacao" width="100" col="0" row="0" enabled="false" />
				<button name="btnErosion" text="Erosao" width="100" col="1" row="0" enabled="false" />

				<button name="btnEdge" text="Bordas" width="100" col="0" row="1" enabled="false" />
				<button name="btnMedian" text="Mediano" width="100" col="1" row="1" enabled="false" />

				<button name="btnBox" text="Borrar" width="100" col="0" row="2" enabled="false" />
				<button name="btnThreshold" text="Limiar" width="100" col="1" row="2" enabled="false" />
			</panel>
		</panel>
		<panel param="center" layout="border">
			<panel layout="flow" param="top" background="false" padding="0" height="20">
				<button name="btnApply" text="Aplicar" width="90" enabled="false" />
				<button name="btnSwap" text="Copiar" width="90" enabled="false" />
				<label name="lblFilter" text="" />
			</panel>
			<panel name="pnlParams" background="false" param="center" layout="grid" gridWidth="4" gridHeight="4">
			</panel>
		</panel>
	</panel>
</root>
)"
